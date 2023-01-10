#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/IGraphicsDevice.hpp>

namespace ag {
class DxGraphicsDevice : public IGraphicsDevice {
public:
    explicit DxGraphicsDevice();

    std::shared_ptr<ITexture> newTexture(int width, int height, const uint8_t* data) const override;
    std::shared_ptr<IBuffer> newVertexBuffer() const override;
    std::shared_ptr<IBuffer> newIndexBuffer() const override;
    std::shared_ptr<RenderingContext> newRenderingContext() const override;

private:
};
}
#endif