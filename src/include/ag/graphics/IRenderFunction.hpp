#pragma once
#include <memory>

namespace ag {
class RenderingContext;

class IRenderFunction {
public:
    using Instance = std::shared_ptr<IRenderFunction>;
    IRenderFunction() = default;
    virtual ~IRenderFunction() = default;
    virtual void draw(const std::shared_ptr<IShader>& shader, const std::shared_ptr<RenderingContext>& context) = 0;
};
}