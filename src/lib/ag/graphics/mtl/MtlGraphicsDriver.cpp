#include <ag/graphics/mtl/MtlGraphicsDriver.hpp>
#ifdef AG_METAL
#include <ag/native/glfw.hpp>

namespace ag {
MtlGraphicsDriver::MtlGraphicsDriver()
{
}

void MtlGraphicsDriver::useWindowHint()
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void MtlGraphicsDriver::useContextExtension()
{
}
std::shared_ptr<IGraphicsDevice> MtlGraphicsDriver::getGraphicsDevice() const { return nullptr; }
std::shared_ptr<IShaderCompiler> MtlGraphicsDriver::getShaderCompiler() const { return nullptr; }
std::shared_ptr<IRenderFunction> MtlGraphicsDriver::getRenderFunction() const { return nullptr; }

}
#endif