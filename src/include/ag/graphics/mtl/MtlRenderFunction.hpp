#pragma once
#ifdef AG_METAL
#include <ag/graphics/IRenderFunction.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
class MtlRenderFunction : public IRenderFunction {
public:
    explicit MtlRenderFunction() = default;
    void begin(const std::shared_ptr<Window>& window) override;
    void draw(const std::shared_ptr<RenderingObject>& object) override;
    void end(const std::shared_ptr<Window>& window) override;

private:
};
}
#endif