#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#ifndef AG_OPEN_GL
#define GLFW_INCLUDE_NONE
#endif
#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace ag {
#if __APPLE__
void* getCocoaWindow(GLFWwindow* window);
#endif
}