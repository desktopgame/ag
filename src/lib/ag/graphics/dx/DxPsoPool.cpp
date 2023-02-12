#ifdef AG_DIRECT_X
#include <ag/graphics/dx/DxPsoPool.hpp>

namespace ag {
DxPsoPool::DxPsoPool(ID3D12Device* device)
    : m_device(device)
    , m_psoVec()
{
}
DxPso::Instance DxPsoPool::rent(
    const std::shared_ptr<DxShader>& shader,
    const std::shared_ptr<ShaderParameter>& shaderParameter,
    PrimitiveType primitiveType,
    int vertexComponent,
    bool isUsingTexCoord)
{
    for (auto pso : m_psoVec) {
        if (pso->getShader() == shader && pso->getShaderParameter() == shaderParameter && pso->getPrimitiveType() == primitiveType && pso->getVertexComponent() == vertexComponent && pso->isUsingTexCoord() == isUsingTexCoord && !pso->isDirty()) {
            pso->update();
            return pso;
        }
    }
    auto newPso = std::make_shared<DxPso>(shader, shaderParameter, primitiveType, vertexComponent, isUsingTexCoord);
    newPso->init(m_device);
    m_psoVec.push_back(newPso);
    return newPso;
}
void DxPsoPool::releaseAll()
{
    for (auto pso : m_psoVec) {
        pso->clear();
    }
}
}
#endif