#include <ag/native/glfw.hpp>
// GLFW
#if __APPLE__
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include <GLFW/glfw3native.h>

namespace ag {
#if __APPLE__
void* getCocoaWindow(GLFWwindow* window)
{
    return glfwGetCocoaWindow(window);
}
#endif
}