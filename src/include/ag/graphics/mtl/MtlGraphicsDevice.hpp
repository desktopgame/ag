#pragma once
#include <ag/graphics/IGraphicsDevice.hpp>

namespace ag {
class MtlGraphicsDevice : public IGraphicsDevice {
public:
    explicit MtlGraphicsDevice();
    std::shared_ptr<ITexture> newTexture(int width, int height, const uint8_t* data) const override;
    std::shared_ptr<IBuffer> newVertexBuffer() const override;
    std::shared_ptr<IBuffer> newIndexBuffer() const override;

private:
};
}