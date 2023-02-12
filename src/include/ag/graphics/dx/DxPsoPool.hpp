#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/dx/DxPso.hpp>
#include <memory>
#include <vector>

namespace ag {
class DxPsoPool {
public:
    explicit DxPsoPool(ID3D12Device* device);
    DxPso::Instance rent(
        const std::shared_ptr<DxShader>& shader,
        const std::shared_ptr<ShaderParameter>& shaderParameter,
        PrimitiveType primitiveType,
        int vertexComponent,
        bool isUsingTexCoord);
    void releaseAll();

private:
    ID3D12Device* m_device;
    std::vector<DxPso::Instance> m_psoVec;
};
}
#endif