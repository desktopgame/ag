#ifdef AG_DIRECT_X
#include <ag/Engine.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/dx/DxGraphicsDevice.hpp>
#include <ag/graphics/dx/DxPso.hpp>
#include <ag/graphics/dx/DxPsoPool.hpp>
#include <ag/graphics/dx/DxRenderFunction.hpp>
#include <ag/graphics/dx/DxRenderingContext.hpp>
#include <ag/graphics/dx/DxSurface.hpp>

namespace ag {
void DxRenderingContext::draw(const std::shared_ptr<IShader>& shader, PrimitiveType primitiveType, int primCount)
{
    if (!shader) {
        return;
    }
    auto dxRenderFunction = std::static_pointer_cast<DxRenderFunction>(Engine::getInstance()->getGraphicsDriver()->getRenderFunction());
    auto dxSurface = dxRenderFunction->getSurface();
    auto dxPsoPool = dxRenderFunction->getPsoCache();
    auto dxShader = std::static_pointer_cast<DxShader>(shader);
    auto dxVertex = std::static_pointer_cast<DxBuffer>(m_vertex);
    auto dxIndex = std::static_pointer_cast<DxBuffer>(m_index);
    auto pso = dxPsoPool->rent(dxShader, m_parameter, primitiveType, m_vertexComponent, m_isUsingTexCoord);
    if (m_indexLength > 0) {
        dxSurface->draw(pso, dxVertex, dxIndex, static_cast<int>(m_indexLength));
    } else {
        dxSurface->draw(pso, dxVertex, static_cast<int>(m_vertexLength));
    }
}
}
#endif