#pragma once
#include <memory>

namespace ag {
class Window;
class RenderPass;
class RenderingObject;

class IRenderFunction {
public:
    using Instance = std::shared_ptr<IRenderFunction>;
    IRenderFunction() = default;
    virtual ~IRenderFunction() = default;
    virtual void begin(const std::shared_ptr<Window>& window, const RenderPass& pass) = 0;
    virtual void end() = 0;
};
}