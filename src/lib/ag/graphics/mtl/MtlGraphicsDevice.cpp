#include <ag/graphics/mtl/MtlGraphicsDevice.hpp>

namespace ag {
MtlGraphicsDevice::MtlGraphicsDevice()
{
}
std::shared_ptr<ITexture> MtlGraphicsDevice::newTexture(int width, int height, const uint8_t* data) const
{
    return nullptr;
}
std::shared_ptr<IBuffer> MtlGraphicsDevice::newVertexBuffer() const
{
    return nullptr;
}
std::shared_ptr<IBuffer> MtlGraphicsDevice::newIndexBuffer() const
{
    return nullptr;
}
}