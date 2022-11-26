#pragma once
#include <ag/graphics/IRenderFunction.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
class OglRenderFunction : public IRenderFunction {
public:
    explicit OglRenderFunction() = default;
    void draw(const std::shared_ptr<RenderingObject>& object) override;

private:
    static GLenum convPrimitiveType(PrimitiveType type);
};
}