#ifdef AG_OPEN_GL
#include <ag/graphics/ogl/OglBuffer.hpp>
#include <ag/graphics/ogl/OglGraphicsDevice.hpp>
#include <ag/graphics/ogl/OglRenderingContext.hpp>
#include <ag/graphics/ogl/OglTexture.hpp>

namespace ag {

OglGraphicsDevice::OglGraphicsDevice() { }
std::shared_ptr<ITexture> OglGraphicsDevice::newTexture(int width, int height, const uint8_t* data) const
{
    auto tex = std::make_shared<OglTexture>();
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
std::shared_ptr<RenderingContext> OglGraphicsDevice::newRenderingContext() const
{
    return std::make_shared<OglRenderingContext>();
}
}
#endif