#pragma once
#include <ag/graphics/IRenderFunction.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
class MtlRenderFunction : public IRenderFunction {
public:
    explicit MtlRenderFunction() = default;
    void draw(const std::shared_ptr<RenderingObject>& object) override;

private:
};
}