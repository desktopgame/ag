#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/dx/DxPso.hpp>
#include <memory>
#include <vector>

namespace ag {
class DxPsoCache {
public:
    explicit DxPsoCache(ID3D12Device* device);
    DxPso::Instance fetch(
        const std::shared_ptr<DxShader>& shader,
        const std::shared_ptr<ShaderParameter>& shaderParameter,
        PrimitiveType primitiveType,
        int vertexComponent,
        bool isUsingTexCoord);

private:
    ID3D12Device* m_device;
    std::vector<DxPso::Instance> m_psoVec;
};
}
#endif