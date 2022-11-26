#pragma once
#include <memory>

namespace ag {
class RenderingObject;

class IRenderFunction {
public:
    using Instance = std::shared_ptr<IRenderFunction>;
    IRenderFunction() = default;
    virtual ~IRenderFunction() = default;
    virtual void draw(const std::shared_ptr<RenderingObject>& object) = 0;
};
}