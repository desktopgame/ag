#ifdef AG_DIRECT_X
#include <ag/Engine.hpp>
#include <ag/graphics/dx/DxGraphicsDevice.hpp>
#include <ag/graphics/dx/DxGraphicsDriver.hpp>
#include <ag/graphics/dx/DxPsoPool.hpp>

namespace ag {
DxPsoPool::DxPsoPool()
    : m_psoVec()
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
        if (pso->getShader() == shader && pso->getShaderParameter() == shaderParameter && pso->getPrimitiveType() == primitiveType && pso->getVertexComponent() == vertexComponent && pso->isUsingTexCoord() == isUsingTexCoord && pso->getTexture() == shaderParameter->getTexture() && !pso->isDirty()) {
            pso->update();
            return pso;
        }
    }
    auto dxGraphicsDevice = std::static_pointer_cast<DxGraphicsDevice>(Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice());
    auto newPso = dxGraphicsDevice->newPso(shader, shaderParameter, primitiveType, vertexComponent, isUsingTexCoord);
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