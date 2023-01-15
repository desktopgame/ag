#pragma once

// GLEW
#ifdef AG_OPEN_GL
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#ifndef AG_OPEN_GL
#define GLFW_INCLUDE_NONE
#endif
#include <GLFW/glfw3.h>

#ifdef AG_DIRECT_X
#include <Windows.h>
#endif

struct GLFWwindow;

namespace ag {
#if __APPLE__
void* getCocoaWindow(GLFWwindow* window);
#endif

#ifdef _WIN32
#ifdef AG_DIRECT_X
HWND getWin32Window(GLFWwindow* window);
#endif
#endif
}