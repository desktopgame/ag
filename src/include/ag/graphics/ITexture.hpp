#pragma once
#include <ag/native/glm.hpp>
#include <memory>

namespace ag {
class ITexture {
public:
    using Instance = std::shared_ptr<ITexture>;
    ITexture() = default;
    virtual ~ITexture() = default;

    virtual void update(int width, int height, const uint8_t* pixels) = 0;
    virtual size_t getWidth() const = 0;
    virtual size_t getHeight() const = 0;
};
}