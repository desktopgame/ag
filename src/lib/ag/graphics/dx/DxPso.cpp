#ifdef AG_DIRECT_X
#include <DirectXMath.h>
#include <ag/graphics/dx/DxPso.hpp>
#include <ag/graphics/dx/DxTexture.hpp>
#include <ag/graphics/dx/DxUtil.hpp>
#include <iostream>
#include <stdexcept>

namespace ag {
DxPso::DxPso(
    const std::shared_ptr<DxShader>& shader,
    const std::shared_ptr<ShaderParameter>& shaderParameter,
    PrimitiveType primitiveType,
    int vertexComponent,
    bool isUsingTexCoord)
    : m_shader(shader)
    , m_shaderParameter(shaderParameter)
    , m_primitiveType(primitiveType)
    , m_vertexComponent(vertexComponent)
    , m_isUsingTexCoord(isUsingTexCoord)
    , m_texture(nullptr)
    , m_isDirty(false)
    , m_pipelineState(nullptr)
    , m_rootSignature(nullptr)
    , m_descriptorHeap(nullptr)
    , m_matrixBuff(nullptr)
    , m_colorBuff(nullptr)
    , m_descriptorHandleIncrementSize(0)
{
}

void DxPso::init(ComPtr<ID3D12Device> device)
{
    if (m_pipelineState) {
        return;
    }
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    // input layout
    std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout;
    if (m_vertexComponent == 3) {
        inputLayout.push_back(
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
                D3D12_APPEND_ALIGNED_ELEMENT,
                D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
    } else {
        inputLayout.push_back(
            { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
                D3D12_APPEND_ALIGNED_ELEMENT,
                D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
    }
    if (m_isUsingTexCoord) {
        inputLayout.push_back(
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
                D3D12_APPEND_ALIGNED_ELEMENT,
                D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
    }
    psoDesc.InputLayout.pInputElementDescs = inputLayout.data();
    psoDesc.InputLayout.NumElements = inputLayout.size();
    // shader
    psoDesc.VS.pShaderBytecode = m_shader->getVSBlob()->GetBufferPointer();
    psoDesc.VS.BytecodeLength = m_shader->getVSBlob()->GetBufferSize();
    psoDesc.PS.pShaderBytecode = m_shader->getPSBlob()->GetBufferPointer();
    psoDesc.PS.BytecodeLength = m_shader->getPSBlob()->GetBufferSize();
    // rasterize
    psoDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
    psoDesc.RasterizerState.MultisampleEnable = false;
    psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
    psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
    psoDesc.RasterizerState.DepthClipEnable = true;
    // depth
    psoDesc.DepthStencilState.DepthEnable = m_vertexComponent == 3;
    psoDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
    psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
    psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
    // blend
    psoDesc.BlendState.AlphaToCoverageEnable = false;
    psoDesc.BlendState.IndependentBlendEnable = false;
    D3D12_RENDER_TARGET_BLEND_DESC rtBlendDesc = {};
    rtBlendDesc.BlendEnable = false;
    rtBlendDesc.LogicOpEnable = false;
    rtBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
    rtBlendDesc.BlendEnable = m_vertexComponent == 2;
    rtBlendDesc.LogicOpEnable = false;
    rtBlendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
    rtBlendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
    rtBlendDesc.BlendOp = D3D12_BLEND_OP_ADD;
    rtBlendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
    rtBlendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;
    rtBlendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
    rtBlendDesc.LogicOp = D3D12_LOGIC_OP_NOOP;
    psoDesc.BlendState.RenderTarget[0] = rtBlendDesc;
    psoDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
    psoDesc.PrimitiveTopologyType = convPrimitiveTopologyType(m_primitiveType);
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.SampleDesc.Count = 1;
    psoDesc.SampleDesc.Quality = 0;
    // root signature
    std::vector<D3D12_DESCRIPTOR_RANGE> descTableRange;
    descTableRange.push_back({});
    descTableRange.at(0).NumDescriptors = 1;
    descTableRange.at(0).RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
    descTableRange.at(0).BaseShaderRegister = 0;
    descTableRange.at(0).OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
    if (m_shaderParameter->useTexture()) {
        descTableRange.push_back({});
        descTableRange.at(1).NumDescriptors = 1;
        descTableRange.at(1).RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
        descTableRange.at(1).BaseShaderRegister = 0;
        descTableRange.at(1).OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

        if (m_shaderParameter->useColor()) {
            descTableRange.push_back({});
            descTableRange.at(2).NumDescriptors = 1;
            descTableRange.at(2).RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
            descTableRange.at(2).BaseShaderRegister = 1;
            descTableRange.at(2).OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
        }
    } else if (m_shaderParameter->useColor()) {
        descTableRange.push_back({});
        descTableRange.at(1).NumDescriptors = 1;
        descTableRange.at(1).RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
        descTableRange.at(1).BaseShaderRegister = 1;
        descTableRange.at(1).OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
    }
    std::vector<D3D12_ROOT_PARAMETER> rootParam;
    rootParam.push_back({});
    rootParam.at(0).ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    rootParam.at(0).ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
    rootParam.at(0).DescriptorTable.pDescriptorRanges = &descTableRange.at(0);
    rootParam.at(0).DescriptorTable.NumDescriptorRanges = 1;

    if (m_shaderParameter->useTexture()) {
        rootParam.push_back({});
        rootParam.at(1).ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
        rootParam.at(1).ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
        rootParam.at(1).DescriptorTable.pDescriptorRanges = &descTableRange.at(1);
        rootParam.at(1).DescriptorTable.NumDescriptorRanges = 1;

        if (m_shaderParameter->useColor()) {
            rootParam.push_back({});
            rootParam.at(2).ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
            rootParam.at(2).ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
            rootParam.at(2).DescriptorTable.pDescriptorRanges = &descTableRange.at(2);
            rootParam.at(2).DescriptorTable.NumDescriptorRanges = 1;
        }
    } else if (m_shaderParameter->useColor()) {
        rootParam.push_back({});
        rootParam.at(1).ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
        rootParam.at(1).ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
        rootParam.at(1).DescriptorTable.pDescriptorRanges = &descTableRange.at(1);
        rootParam.at(1).DescriptorTable.NumDescriptorRanges = 1;
    }
    D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
    samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
    samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
    samplerDesc.MinLOD = 0.0f;
    samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
    D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
    rootSignatureDesc.pParameters = rootParam.data();
    rootSignatureDesc.NumParameters = rootParam.size();
    rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    rootSignatureDesc.pStaticSamplers = &samplerDesc;
    rootSignatureDesc.NumStaticSamplers = 1;
    ID3DBlob* rootSigBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;
    if (FAILED(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob))) {
        std::cerr << DxUtil::getString(errorBlob) << std::endl;
        throw std::runtime_error("failed D3D12SerializeRootSignature()");
    }
    if (FAILED(device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(m_rootSignature.ReleaseAndGetAddressOf())))) {
        throw std::runtime_error("failed CreateRootSignature()");
    }
    psoDesc.pRootSignature = m_rootSignature.Get();
    if (FAILED(device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(m_pipelineState.ReleaseAndGetAddressOf())))) {
        throw std::runtime_error("failed CreateGraphicsPipelineState()");
    }
    // descriptor heap
    D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
    descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    descHeapDesc.NodeMask = 0;
    descHeapDesc.NumDescriptors = 1;
    if (m_shaderParameter->useTexture()) {
        descHeapDesc.NumDescriptors++;
    }
    if (m_shaderParameter->useColor()) {
        descHeapDesc.NumDescriptors++;
    }
    descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    if (FAILED(device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(m_descriptorHeap.ReleaseAndGetAddressOf())))) {
        throw std::runtime_error("failed CreateDescriptorHeap()");
    }
    m_descriptorHandleIncrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Waddress-of-temporary"
    // transform
    if (!m_matrixBuff) {
        if (FAILED(device->CreateCommittedResource(
                &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
                D3D12_HEAP_FLAG_NONE,
                &CD3DX12_RESOURCE_DESC::Buffer((sizeof(glm::mat4) + 0xff) & ~0xff),
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(m_matrixBuff.ReleaseAndGetAddressOf())))) {
            throw std::runtime_error("failed CreateCommittedResource()");
        }
    }
    // color
    if (m_shaderParameter->useColor()) {
        if (!m_colorBuff) {
            if (FAILED(device->CreateCommittedResource(
                    &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
                    D3D12_HEAP_FLAG_NONE,
                    &CD3DX12_RESOURCE_DESC::Buffer((sizeof(glm::vec4) + 0xff) & ~0xff),
                    D3D12_RESOURCE_STATE_GENERIC_READ,
                    nullptr,
                    IID_PPV_ARGS(m_colorBuff.ReleaseAndGetAddressOf())))) {
                throw std::runtime_error("failed CreateCommittedResource()");
            }
        }
    }
    update();
    this->m_isDirty = false;
    // constant buffer
    auto basicHeapHandle = m_descriptorHeap->GetCPUDescriptorHandleForHeapStart();
    // constant buffer(matrix)
    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvMatrixDesc = {};
    cbvMatrixDesc.BufferLocation = m_matrixBuff->GetGPUVirtualAddress();
    cbvMatrixDesc.SizeInBytes = m_matrixBuff->GetDesc().Width;
    device->CreateConstantBufferView(&cbvMatrixDesc, basicHeapHandle);
    // constant buffer(color)

    if (m_shaderParameter->useTexture()) {
        basicHeapHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1;
        auto texBuff = std::static_pointer_cast<DxTexture>(m_shaderParameter->getTexture())->getResource();
        device->CreateShaderResourceView(texBuff, &srvDesc, basicHeapHandle);

        if (m_shaderParameter->useColor()) {
            basicHeapHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
            D3D12_CONSTANT_BUFFER_VIEW_DESC cbvColorDesc = {};
            cbvColorDesc.BufferLocation = m_colorBuff->GetGPUVirtualAddress();
            cbvColorDesc.SizeInBytes = m_colorBuff->GetDesc().Width;
            device->CreateConstantBufferView(&cbvColorDesc, basicHeapHandle);
        }
    } else if (m_shaderParameter->useColor()) {
        basicHeapHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
        D3D12_CONSTANT_BUFFER_VIEW_DESC cbvColorDesc = {};
        cbvColorDesc.BufferLocation = m_colorBuff->GetGPUVirtualAddress();
        cbvColorDesc.SizeInBytes = m_colorBuff->GetDesc().Width;
        device->CreateConstantBufferView(&cbvColorDesc, basicHeapHandle);
    }
#pragma clang diagnostic pop
    m_texture = m_shaderParameter->getTexture();
}

void DxPso::update()
{
    updateTransform();
    updateColor();
    this->m_isDirty = true;
}

void DxPso::command(ID3D12GraphicsCommandList* cmdList)
{
    cmdList->SetPipelineState(m_pipelineState.Get());
    cmdList->SetGraphicsRootSignature(m_rootSignature.Get());

    auto heapHandle = m_descriptorHeap->GetGPUDescriptorHandleForHeapStart();
    cmdList->SetDescriptorHeaps(1, m_descriptorHeap.GetAddressOf());
    cmdList->SetGraphicsRootDescriptorTable(0, heapHandle);
    if (m_shaderParameter->useTexture()) {
        heapHandle.ptr += m_descriptorHandleIncrementSize;
        cmdList->SetGraphicsRootDescriptorTable(1, heapHandle);
        if (m_shaderParameter->useColor()) {
            heapHandle.ptr += m_descriptorHandleIncrementSize;
            cmdList->SetGraphicsRootDescriptorTable(2, heapHandle);
        }
    } else if (m_shaderParameter->useColor()) {
        heapHandle.ptr += m_descriptorHandleIncrementSize;
        cmdList->SetGraphicsRootDescriptorTable(1, heapHandle);
    }
    cmdList->IASetPrimitiveTopology(convPrimitiveTopology(m_primitiveType));
}

void DxPso::clear() { m_isDirty = false; }

std::shared_ptr<DxShader> DxPso::getShader() const { return m_shader; }
std::shared_ptr<ShaderParameter> DxPso::getShaderParameter() const { return m_shaderParameter; }
PrimitiveType DxPso::getPrimitiveType() const { return m_primitiveType; }
int DxPso::getVertexComponent() const { return m_vertexComponent; }
bool DxPso::isUsingTexCoord() const { return m_isUsingTexCoord; }
std::shared_ptr<ITexture> DxPso::getTexture() const { return m_texture; }
bool DxPso::isDirty() const { return m_isDirty; }
// private
D3D_PRIMITIVE_TOPOLOGY DxPso::convPrimitiveTopology(PrimitiveType primitiveType)
{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch"
    switch (primitiveType) {
    case PrimitiveType::Triangles:
        return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    case PrimitiveType::LineStrip:
        return D3D_PRIMITIVE_TOPOLOGY_LINESTRIP;
    }
#pragma clang diagnostic pop
    return D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
}
D3D12_PRIMITIVE_TOPOLOGY_TYPE DxPso::convPrimitiveTopologyType(PrimitiveType primitiveType)
{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch"
    switch (primitiveType) {
    case PrimitiveType::Triangles:
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    case PrimitiveType::LineStrip:
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
    }
#pragma clang diagnostic pop
    return D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED;
}

void DxPso::updateTransform()
{
    void* mapMatrix = nullptr;
    if (FAILED(m_matrixBuff->Map(0, nullptr, (void**)&mapMatrix))) {
        throw std::runtime_error("failed Map()");
    } else {
        auto matrix = m_shaderParameter->getTransform();
        ::memcpy(mapMatrix, glm::value_ptr(matrix), sizeof(glm::mat4));
        m_matrixBuff->Unmap(0, nullptr);
    }
}
void DxPso::updateColor()
{
    if (!m_shaderParameter->useColor()) {
        return;
    }
    void* mapColor = nullptr;
    if (FAILED(m_colorBuff->Map(0, nullptr, (void**)&mapColor))) {
        throw std::runtime_error("failed Map()");
    } else {
        auto color = m_shaderParameter->getColor();
        ::memcpy(mapColor, glm::value_ptr(color), sizeof(glm::vec4));
        m_colorBuff->Unmap(0, nullptr);
    }
}
}
#endif