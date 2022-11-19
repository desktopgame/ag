#include <ag/graphics/mtl/MtlGraphicsDriver.hpp>
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
}