#pragma once
#ifdef AG_OPEN_GL
#include <ag/graphics/IGraphicsDevice.hpp>

namespace ag {
class OglGraphicsDevice : public IGraphicsDevice {
public:
    explicit OglGraphicsDevice();
    std::shared_ptr<ITexture> newTexture(int width, int height, const uint8_t* data) const override;
    std::shared_ptr<IBuffer> newVertexBuffer() const override;
    std::shared_ptr<IBuffer> newIndexBuffer() const override;

private:
};
}
#endif