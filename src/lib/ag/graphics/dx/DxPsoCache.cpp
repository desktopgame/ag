#ifdef AG_DIRECT_X
#include <ag/graphics/dx/DxPsoCache.hpp>

namespace ag {
DxPsoCache::DxPsoCache(ID3D12Device* device)
    : m_device(device)
    , m_psoVec()
{
}
DxPso::Instance DxPsoCache::fetch(
    const std::shared_ptr<DxShader>& shader,
    const std::shared_ptr<ShaderParameter>& shaderParameter,
    PrimitiveType primitiveType,
    int vertexComponent,
    bool isUsingTexCoord)
{
    for (auto pso : m_psoVec) {
        if (pso->getShader() == shader && pso->getShaderParameter() == shaderParameter && pso->getPrimitiveType() == primitiveType && pso->getVertexComponent() == vertexComponent && pso->isUsingTexCoord() == isUsingTexCoord) {
            return pso;
        }
    }
    auto newPso = std::make_shared<DxPso>(shader, shaderParameter, primitiveType, vertexComponent, isUsingTexCoord);
    newPso->init(m_device);
    m_psoVec.push_back(newPso);
    return newPso;
}
}
#endif