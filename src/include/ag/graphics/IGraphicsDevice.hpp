#pragma once
#include <memory>

namespace ag {
class ITexture;
class IBuffer;
class IShaderParameter;
class IGraphicsDevice {
public:
    using Instance = std::shared_ptr<IGraphicsDevice>;
    IGraphicsDevice() = default;
    virtual ~IGraphicsDevice() = default;

    virtual std::shared_ptr<ITexture> newTexture(int width, int height, const uint8_t* data) const = 0;
    virtual std::shared_ptr<IBuffer> newVertexBuffer() const = 0;
    virtual std::shared_ptr<IBuffer> newIndexBuffer() const = 0;
    virtual std::shared_ptr<IShaderParameter> newShaderParameter() const = 0;
};
}