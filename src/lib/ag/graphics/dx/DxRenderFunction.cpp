#ifdef AG_DIRECT_X
#include <ag/Engine.hpp>
#include <ag/Window.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/dx/DxGraphicsDevice.hpp>
#include <ag/graphics/dx/DxRenderFunction.hpp>
#include <ag/graphics/dx/DxSurface.hpp>

namespace ag {
DxRenderFunction::DxRenderFunction()
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
void DxRenderFunction::begin(const std::shared_ptr<Window>& window, const RenderPass& pass) { }
void DxRenderFunction::end() { }
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
}
#endif