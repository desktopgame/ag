#pragma once
#include <memory>

namespace ag {
class Window;
class RenderingObject;

class IRenderFunction {
public:
    using Instance = std::shared_ptr<IRenderFunction>;
    IRenderFunction() = default;
    virtual ~IRenderFunction() = default;
    virtual void begin(const std::shared_ptr<Window>& window) = 0;
    virtual void draw(const std::shared_ptr<RenderingObject>& object) = 0;
    virtual void end(const std::shared_ptr<Window>& window) = 0;
};
}