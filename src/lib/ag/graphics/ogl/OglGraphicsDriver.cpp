#include <ag/graphics/ogl/OglGraphicsDriver.hpp>
#include <ag/graphics/ogl/OglRenderFunction.hpp>
#include <ag/graphics/ogl/OglShaderCompiler.hpp>
#include <ag/native/glfw.hpp>
#include <stdexcept>

namespace ag {
OglGraphicsDriver::OglGraphicsDriver()
    : m_device(std::make_shared<OglGraphicsDevice>())
    , m_shaderCompiler(std::make_shared<OglShaderCompiler>())
    , m_renderFunction(std::make_shared<OglRenderFunction>())
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
std::shared_ptr<IShaderCompiler> OglGraphicsDriver::getShaderCompiler() const
{
    return m_shaderCompiler;
}
std::shared_ptr<IRenderFunction> OglGraphicsDriver::getRenderFunction() const
{
    return m_renderFunction;
}
}