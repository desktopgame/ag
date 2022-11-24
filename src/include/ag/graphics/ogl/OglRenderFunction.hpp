#pragma once
#include <ag/graphics/IRenderFunction.hpp>

namespace ag {
class OglRenderFunction : public IRenderFunction {
public:
    explicit OglRenderFunction() = default;
    void draw(const std::shared_ptr<IShader>& shader, const std::shared_ptr<RenderingContext>& context) override;
};
}