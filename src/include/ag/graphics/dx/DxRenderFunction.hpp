#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/IRenderFunction.hpp>

namespace ag {
class DxRenderFunction : public IRenderFunction {
public:
    explicit DxRenderFunction();
    void link(const std::shared_ptr<Window>& window) override;
    void begin(const std::shared_ptr<Window>& window, const RenderPass& pass) override;
    void end() override;
    void clear(const std::shared_ptr<Window>& window) override;
    void present(const std::shared_ptr<Window>& window) override;

private:
};
}
#endif