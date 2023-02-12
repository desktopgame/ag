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
    void init(ID3D12Device* device);
    void command(ID3D12GraphicsCommandList* cmdList);

    std::shared_ptr<DxShader> getShader() const;
    std::shared_ptr<ShaderParameter> getShaderParameter() const;
    PrimitiveType getPrimitiveType() const;
    int getVertexComponent() const;
    bool isUsingTexCoord() const;

private:
    static D3D_PRIMITIVE_TOPOLOGY convPrimitiveTopology(PrimitiveType primitiveType);
    static D3D12_PRIMITIVE_TOPOLOGY_TYPE convPrimitiveTopologyType(PrimitiveType primitiveType);

    std::shared_ptr<DxShader> m_shader;
    std::shared_ptr<ShaderParameter> m_shaderParameter;
    PrimitiveType m_primitiveType;
    int m_vertexComponent;
    bool m_isUsingTexCoord;
    // PSO
    ID3D12PipelineState* m_pipelineState;
    ID3D12RootSignature* m_rootSignature;
    ID3D12DescriptorHeap* m_descriptorHeap;
    ID3D12Resource* m_matrixBuff;
    ID3D12Resource* m_colorBuff;
    int m_descriptorHandleIncrementSize;
};
}
#endif