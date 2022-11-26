#include <ag/graphics/ogl/OglGraphicsDriver.hpp>
#include <ag/graphics/ogl/OglRenderFunction.hpp>
#include <ag/graphics/ogl/OglShaderCompiler.hpp>
#include <ag/native/glfw.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

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
#ifdef AG_DEBUG
    std::vector<std::string> versions {
        "GL_VERSION_1_1",
        "GL_VERSION_2_1",
        "GL_VERSION_3_0",
        "GL_VERSION_3_1",
        "GL_VERSION_3_2",
        "GL_VERSION_3_3",
        "GL_VERSION_4_1",
    };
    for (const std::string& version : versions) {
        bool supported = glewIsSupported(version.c_str());
        if (supported) {
            std::cout << "OpenGL " << version << " is supported!" << std::endl;
        } else {
            std::cout << "OpenGL " << version << " is not supported!" << std::endl;
        }
    }
#endif
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