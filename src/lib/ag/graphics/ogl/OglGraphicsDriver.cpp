#include <ag/graphics/ogl/OglGraphicsDriver.hpp>
#include <ag/native/glfw.hpp>
#include <stdexcept>

namespace ag {
OglGraphicsDriver::OglGraphicsDriver()
    : m_device(std::make_shared<OglGraphicsDevice>())
{
}

void OglGraphicsDriver::useWindowHint()
{
}

void OglGraphicsDriver::useContextExtension()
{
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        throw std::runtime_error("glew is unavailable.");
    }
}
std::shared_ptr<IGraphicsDevice> OglGraphicsDriver::getGraphicsDevice() const
{
    return m_device;
}
}