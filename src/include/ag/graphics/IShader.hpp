#pragma once
#include <memory>

namespace ag {
class IShaderParameter;
class IShader {
public:
    using Instance = std::shared_ptr<IShader>;
    IShader() = default;
    virtual ~IShader() = default;
    virtual void apply(const std::shared_ptr<IShaderParameter>& parameter) = 0;
};
}