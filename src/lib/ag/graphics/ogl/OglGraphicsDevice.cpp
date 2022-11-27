#ifdef AG_OPEN_GL
#include <ag/graphics/ogl/OglBuffer.hpp>
#include <ag/graphics/ogl/OglGraphicsDevice.hpp>
#include <ag/graphics/ogl/OglTexture.hpp>

namespace ag {

OglGraphicsDevice::OglGraphicsDevice() { }
std::shared_ptr<ITexture> OglGraphicsDevice::newTexture(int width, int height, const uint8_t* data) const
{
    auto tex = std::shared_ptr<OglTexture>();
    tex->update(width, height, data);
    return tex;
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
#endif