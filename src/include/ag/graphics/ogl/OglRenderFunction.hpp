#pragma once
#ifdef AG_OPEN_GL
#include <ag/graphics/IRenderFunction.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
class OglRenderFunction : public IRenderFunction {
public:
    explicit OglRenderFunction() = default;
    void begin(const std::shared_ptr<Window>& window) override;
    void end(const std::shared_ptr<Window>& window) override;

private:
};
}
#endif