#include <ag/native/glfw.hpp>
// GLFW
#if __APPLE__
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#if _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#include <GLFW/glfw3native.h>

namespace ag {
#if __APPLE__
void* getCocoaWindow(GLFWwindow* window)
{
    return glfwGetCocoaWindow(window);
}
#endif

#ifdef _WIN32
HWND getWin32Window(GLFWwindow* window)
{
    return glfwGetWin32Window(window);
}
#endif
}