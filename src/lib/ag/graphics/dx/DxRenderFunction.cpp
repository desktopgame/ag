#ifdef AG_DIRECT_X
#include <ag/Window.hpp>
#include <ag/graphics/dx/DxRenderFunction.hpp>

namespace ag {
DxRenderFunction::DxRenderFunction()
{
}

void DxRenderFunction::link(const std::shared_ptr<Window>& window) { }
void DxRenderFunction::begin(const std::shared_ptr<Window>& window, const RenderPass& pass) { }
void DxRenderFunction::end() { }
void DxRenderFunction::clear(const std::shared_ptr<Window>& window) { }
void DxRenderFunction::present(const std::shared_ptr<Window>& window) { }
}
#endif