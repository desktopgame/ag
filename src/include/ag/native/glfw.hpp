#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace ag {
#if __APPLE__
void* getCocoaWindow(GLFWwindow* window);
#endif
}