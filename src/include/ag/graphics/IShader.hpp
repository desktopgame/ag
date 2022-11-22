#pragma once
#include <memory>

namespace ag {
class IShader {
    using Instance = std::shared_ptr<IShader>;
    IShader() = default;
    virtual ~IShader() = default;
};
}