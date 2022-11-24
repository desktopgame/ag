#include <ag/graphics/ogl/OglBuffer.hpp>
#include <ag/graphics/ogl/OglGraphicsDevice.hpp>

namespace ag {

OglGraphicsDevice::OglGraphicsDevice() { }
std::shared_ptr<ITexture> OglGraphicsDevice::newTexture(int width, int height, const uint8_t* data) const
{
    return nullptr;
}
std::shared_ptr<IBuffer> OglGraphicsDevice::newVertexBuffer() const
{
    return std::make_shared<OglBuffer>(false);
}
std::shared_ptr<IBuffer> OglGraphicsDevice::newIndexBuffer() const
{
    return std::make_shared<OglBuffer>(true);
}
}