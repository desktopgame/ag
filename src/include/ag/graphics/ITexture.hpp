#pragma once
#include <ag/native/glm.hpp>
#include <memory>

namespace ag {
class ITexture {
    using Component = uint8_t;
    using Instance = std::shared_ptr<ITexture>;
    ITexture() = default;
    virtual ~ITexture() = default;

    virtual void update(const Component* pixels) = 0;
    virtual size_t getWidth() const = 0;
    virtual size_t getHeight() const = 0;
};
}