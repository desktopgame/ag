#ifdef AG_DIRECT_X
#include <ag/Engine.hpp>
#include <ag/Window.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/dx/DxGraphicsDevice.hpp>
#include <ag/graphics/dx/DxRenderFunction.hpp>
#include <ag/graphics/dx/DxSurface.hpp>

namespace ag {
DxRenderFunction::DxRenderFunction(ID3D12Device* device)
    : m_psoCache(std::make_shared<DxPsoCache>(device))
{
}

void DxRenderFunction::link(const std::shared_ptr<Window>& window)
{
    if (window->getSurfaceObject().has_value()) {
        return;
    }
    auto surface = std::static_pointer_cast<DxGraphicsDevice>(Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice())->newSurface(window);
    window->setSurfaceObject(surface);
}
void DxRenderFunction::begin(const std::shared_ptr<Window>& window, const RenderPass& pass)
{
    m_surface = std::any_cast<std::shared_ptr<DxSurface>>(window->getSurfaceObject());
}
void DxRenderFunction::end()
{
    m_surface = nullptr;
}
void DxRenderFunction::clear(const std::shared_ptr<Window>& window)
{
    auto surface = std::any_cast<std::shared_ptr<DxSurface>>(window->getSurfaceObject());
    surface->transitionPresentToRender();
    surface->clear(window->getClearColor());
}
void DxRenderFunction::present(const std::shared_ptr<Window>& window)
{
    auto surface = std::any_cast<std::shared_ptr<DxSurface>>(window->getSurfaceObject());
    surface->transitionRenderToPresent();
    surface->execute();
    surface->waitSync();
    surface->reset();
    surface->present();
}
std::shared_ptr<DxPsoCache> DxRenderFunction::getPsoCache() const { return m_psoCache; }
std::shared_ptr<DxSurface> DxRenderFunction::getSurface() const { return m_surface; }
}
#endif