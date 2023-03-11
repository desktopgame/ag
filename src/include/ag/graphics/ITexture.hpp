#pragma once
#include <ag/native/glm.hpp>
#include <memory>

namespace ag {
class ITexture {
public:
    using Instance = std::shared_ptr<ITexture>;
    ITexture() = default;
    virtual ~ITexture() = default;

    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
};
}