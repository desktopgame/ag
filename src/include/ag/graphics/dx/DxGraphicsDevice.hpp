#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/IGraphicsDevice.hpp>
#include <ag/native/dx.hpp>

namespace ag {
class DxGraphicsDevice : public IGraphicsDevice {
public:
    explicit DxGraphicsDevice(ID3D12Device* device);

    std::shared_ptr<ITexture> newTexture(int width, int height, const uint8_t* data) const override;
    std::shared_ptr<IBuffer> newVertexBuffer() const override;
    std::shared_ptr<IBuffer> newIndexBuffer() const override;
    std::shared_ptr<RenderingContext> newRenderingContext() const override;

private:
    ID3D12Device* m_device;
};
}
#endif