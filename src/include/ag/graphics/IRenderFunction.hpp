#pragma once
#include <memory>

namespace ag {
class IShader;
class IShaderParameter;
class IBuffer;

class IRenderFunction {
public:
    using Instance = std::shared_ptr<IRenderFunction>;
    IRenderFunction() = default;
    virtual ~IRenderFunction() = default;
    virtual void draw(IShader shader, IShaderParameter params, IBuffer vertex, IBuffer index) = 0;
};
}