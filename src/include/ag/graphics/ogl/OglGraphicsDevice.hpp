#pragma once
#include <ag/graphics/IGraphicsDevice.hpp>

namespace ag {
class OglGraphicsDevice : public IGraphicsDevice {
public:
    explicit OglGraphicsDevice();
    std::shared_ptr<ITexture> newTexture(int width, int height, const uint8_t* data) const override;
    std::shared_ptr<IBuffer> newVertexBuffer() const override;
    std::shared_ptr<IBuffer> newIndexBuffer() const override;
    std::shared_ptr<IShaderParameter> newShaderParameter() const override;

private:
};
}