#include <ag/graphics/dx/DxGraphicsDevice.hpp>

namespace ag {
DxGraphicsDevice::DxGraphicsDevice(ID3D12Device* device)
    : m_device(device)
{
}
std::shared_ptr<ITexture> DxGraphicsDevice::newTexture(int width, int height, const uint8_t* data) const { return nullptr; }
std::shared_ptr<IBuffer> DxGraphicsDevice::newVertexBuffer() const { return nullptr; }
std::shared_ptr<IBuffer> DxGraphicsDevice::newIndexBuffer() const { return nullptr; }
std::shared_ptr<RenderingContext> DxGraphicsDevice::newRenderingContext() const { return nullptr; }

}