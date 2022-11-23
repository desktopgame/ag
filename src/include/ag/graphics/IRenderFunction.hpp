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
    virtual void draw(const std::shared_ptr<IShader>& shader, const std::shared_ptr<IShaderParameter>& parameter, const std::shared_ptr<IBuffer>& vertex, const std::shared_ptr<IBuffer>& index) = 0;
};
}