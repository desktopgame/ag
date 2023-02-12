#ifdef AG_DIRECT_X
#include <ag/graphics/dx/DxPso.hpp>
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
    , m_pipelineState(nullptr)
    , m_rootSignature(nullptr)
    , m_descriptorHeap(nullptr)
    , m_matrixBuff(nullptr)
    , m_colorBuff(nullptr)
    , m_descriptorHandleIncrementSize(0)
{
}

void DxPso::init(ID3D12Device* device)
{
    if (m_pipelineState) {
        return;
    }
    //*
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    // input layout
    std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout;
    inputLayout.push_back(
        { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
            D3D12_APPEND_ALIGNED_ELEMENT,
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
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
    psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
    psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
    psoDesc.RasterizerState.DepthClipEnable = true;
    // blend
    psoDesc.BlendState.AlphaToCoverageEnable = false;
    psoDesc.BlendState.IndependentBlendEnable = false;
    D3D12_RENDER_TARGET_BLEND_DESC rtBlendDesc = {};
    rtBlendDesc.BlendEnable = false;
    rtBlendDesc.LogicOpEnable = false;
    rtBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
    psoDesc.BlendState.RenderTarget[0] = rtBlendDesc;
    psoDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
    psoDesc.PrimitiveTopologyType = convPrimitiveTopologyType(m_primitiveType);
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.SampleDesc.Count = 1;
    psoDesc.SampleDesc.Quality = 0;
    // root signature
    D3D12_DESCRIPTOR_RANGE descTableRange[2] = {};
    descTableRange[0].NumDescriptors = 1;
    descTableRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
    descTableRange[0].BaseShaderRegister = 0;
    descTableRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
    descTableRange[1].NumDescriptors = 1;
    descTableRange[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
    descTableRange[1].BaseShaderRegister = 1;
    descTableRange[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
    D3D12_ROOT_PARAMETER rootParam[2] = {};
    rootParam[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    rootParam[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
    rootParam[0].DescriptorTable.pDescriptorRanges = &descTableRange[0];
    rootParam[0].DescriptorTable.NumDescriptorRanges = 1;
    rootParam[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    rootParam[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
    rootParam[1].DescriptorTable.pDescriptorRanges = &descTableRange[1];
    rootParam[1].DescriptorTable.NumDescriptorRanges = 1;
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
    rootSignatureDesc.pParameters = rootParam;
    rootSignatureDesc.NumParameters = 2;
    rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    // rootSignatureDesc.pStaticSamplers = &samplerDesc;
    // rootSignatureDesc.NumStaticSamplers = 1;
    ID3DBlob* rootSigBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;
    if (FAILED(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob))) {
        std::cerr << DxUtil::getString(errorBlob) << std::endl;
        throw std::runtime_error("failed D3D12SerializeRootSignature()");
    }
    if (FAILED(device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature)))) {
        throw std::runtime_error("failed CreateRootSignature()");
    }
    psoDesc.pRootSignature = m_rootSignature;
    if (FAILED(device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_pipelineState)))) {
        throw std::runtime_error("failed CreateGraphicsPipelineState()");
    }
    //*/
    // descriptor heap
    D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
    descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    descHeapDesc.NodeMask = 0;
    descHeapDesc.NumDescriptors = 2;
    descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    if (FAILED(device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&m_descriptorHeap)))) {
        throw std::runtime_error("failed CreateDescriptorHeap()");
    }
    m_descriptorHandleIncrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    // color
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Waddress-of-temporary"
    if (m_shaderParameter->useColor()) {
        if (!m_colorBuff) {
            if (FAILED(device->CreateCommittedResource(
                    &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
                    D3D12_HEAP_FLAG_NONE,
                    &CD3DX12_RESOURCE_DESC::Buffer((sizeof(glm::vec4) + 0xff) & ~0xff),
                    D3D12_RESOURCE_STATE_GENERIC_READ,
                    nullptr,
                    IID_PPV_ARGS(&m_colorBuff)))) {
                throw std::runtime_error("failed CreateCommittedResource()");
            }
        }
        void* mapColor = nullptr;
        if (FAILED(m_colorBuff->Map(0, nullptr, (void**)&mapColor))) {
            throw std::runtime_error("failed Map()");
        } else {
            auto color = m_shaderParameter->getColor();
            ::memcpy(mapColor, &color.x, sizeof(glm::vec4));
            m_colorBuff->Unmap(0, nullptr);
        }
    }
    // transform
    if (!m_matrixBuff) {
        if (FAILED(device->CreateCommittedResource(
                &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
                D3D12_HEAP_FLAG_NONE,
                &CD3DX12_RESOURCE_DESC::Buffer((sizeof(glm::mat4) + 0xff) & ~0xff),
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&m_matrixBuff)))) {
            throw std::runtime_error("failed CreateCommittedResource()");
        }
    }
    void* mapMatrix = nullptr;
    if (FAILED(m_matrixBuff->Map(0, nullptr, (void**)&mapMatrix))) {
        throw std::runtime_error("failed Map()");
    } else {
        auto matrix = m_shaderParameter->getTransform();
        ::memcpy(mapMatrix, glm::value_ptr(matrix), sizeof(glm::mat4));
        m_matrixBuff->Unmap(0, nullptr);
    }
    // constant buffer
    auto basicHeapHandle = m_descriptorHeap->GetCPUDescriptorHandleForHeapStart();
    // constant buffer(matrix)
    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvMatrixDesc = {};
    cbvMatrixDesc.BufferLocation = m_matrixBuff->GetGPUVirtualAddress();
    cbvMatrixDesc.SizeInBytes = m_matrixBuff->GetDesc().Width;
    device->CreateConstantBufferView(&cbvMatrixDesc, basicHeapHandle);
    // constant buffer(color)
    basicHeapHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvColorDesc = {};
    cbvColorDesc.BufferLocation = m_colorBuff->GetGPUVirtualAddress();
    cbvColorDesc.SizeInBytes = m_colorBuff->GetDesc().Width;
    device->CreateConstantBufferView(&cbvColorDesc, basicHeapHandle);
#pragma clang diagnostic pop
}

void DxPso::command(ID3D12GraphicsCommandList* cmdList)
{
    cmdList->SetPipelineState(m_pipelineState);
    cmdList->SetGraphicsRootSignature(m_rootSignature);

    auto heapHandle = m_descriptorHeap->GetGPUDescriptorHandleForHeapStart();
    cmdList->SetDescriptorHeaps(1, &m_descriptorHeap);
    cmdList->SetGraphicsRootDescriptorTable(0, heapHandle);
    heapHandle.ptr += m_descriptorHandleIncrementSize;
    cmdList->SetGraphicsRootDescriptorTable(1, heapHandle);
    cmdList->IASetPrimitiveTopology(convPrimitiveTopology(m_primitiveType));
}

std::shared_ptr<DxShader> DxPso::getShader() const { return m_shader; }
std::shared_ptr<ShaderParameter> DxPso::getShaderParameter() const { return m_shaderParameter; }
PrimitiveType DxPso::getPrimitiveType() const { return m_primitiveType; }
int DxPso::getVertexComponent() const { return m_vertexComponent; }
bool DxPso::isUsingTexCoord() const { return m_isUsingTexCoord; }
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
}
#endif