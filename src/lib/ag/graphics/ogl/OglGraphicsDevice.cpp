#include <ag/graphics/ogl/OglGraphicsDevice.hpp>

namespace ag {

OglGraphicsDevice::OglGraphicsDevice() { }
std::shared_ptr<ITexture> OglGraphicsDevice::newTexture(int width, int height, const uint8_t* data) const
{
    return nullptr;
}
std::shared_ptr<IBuffer> OglGraphicsDevice::newVertexBuffer() const
{
    return nullptr;
}
std::shared_ptr<IBuffer> OglGraphicsDevice::newIndexBuffer() const
{
    return nullptr;
}
std::shared_ptr<IShaderParameter> OglGraphicsDevice::newShaderParameter() const
{
    return nullptr;
}
}