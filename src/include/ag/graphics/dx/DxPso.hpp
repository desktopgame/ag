#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/PrimitiveType.hpp>
#include <ag/graphics/ShaderParameter.hpp>
#include <ag/graphics/dx/DxShader.hpp>
#include <ag/native/dx.hpp>
#include <memory>
#include <vector>

namespace ag {
class DxPso {
public:
    using Instance = std::shared_ptr<DxPso>;
    explicit DxPso(
        const std::shared_ptr<DxShader>& shader,
        const std::shared_ptr<ShaderParameter>& shaderParameter,
        PrimitiveType primitiveType,
        int vertexComponent,
        bool isUsingTexCoord);
    void init(ComPtr<ID3D12Device> device);
    void update();
    void clear();
    void command(ID3D12GraphicsCommandList* cmdList);

    std::shared_ptr<DxShader> getShader() const;
    std::shared_ptr<ShaderParameter> getShaderParameter() const;
    PrimitiveType getPrimitiveType() const;
    int getVertexComponent() const;
    bool isUsingTexCoord() const;

    std::shared_ptr<ITexture> getTexture() const;
    bool isDirty() const;

private:
    static D3D_PRIMITIVE_TOPOLOGY convPrimitiveTopology(PrimitiveType primitiveType);
    static D3D12_PRIMITIVE_TOPOLOGY_TYPE convPrimitiveTopologyType(PrimitiveType primitiveType);

    void updateTransform();
    void updateColor();

    std::shared_ptr<DxShader> m_shader;
    std::shared_ptr<ShaderParameter> m_shaderParameter;
    PrimitiveType m_primitiveType;
    int m_vertexComponent;
    bool m_isUsingTexCoord;
    // Pool
    std::shared_ptr<ITexture> m_texture;
    bool m_isDirty;
    // PSO
    ComPtr<ID3D12PipelineState> m_pipelineState;
    ComPtr<ID3D12RootSignature> m_rootSignature;
    ComPtr<ID3D12DescriptorHeap> m_descriptorHeap;
    ComPtr<ID3D12Resource> m_matrixBuff;
    ComPtr<ID3D12Resource> m_colorBuff;
    int m_descriptorHandleIncrementSize;
};
}
#endif