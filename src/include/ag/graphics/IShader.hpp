#pragma once
#include <ag/graphics/ShaderParameter.hpp>
#include <memory>

namespace ag {
class IShader {
public:
    using Instance = std::shared_ptr<IShader>;
    IShader() = default;
    virtual ~IShader() = default;
    virtual void apply(const std::shared_ptr<ShaderParameter>& parameter) = 0;
};
}