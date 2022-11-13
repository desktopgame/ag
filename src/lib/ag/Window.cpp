#include <ag/Engine.hpp>
#include <ag/Window.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
std::vector<Window::Instance> Window::s_windows;

Window::Instance Window::create(int width, int height, const std::string& title)
{
    Engine::require();
    glfwDefaultWindowHints();
    Engine::getInstance()->getGraphicsDriver()->useWindowHint();
    // create window instance.
    GLFWwindow* glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    Window::Instance window = Window::Instance(new Window(glfwWindow));
    Window::s_windows.emplace_back(window);
    return window;
}
bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_glfwWindow);
}
void Window::makeContextCurrent()
{
    Engine::require();
    glfwMakeContextCurrent(m_glfwWindow);
    Engine::getInstance()->getGraphicsDriver()->useContextExtension();
}
void Window::dispose()
{
    if (m_disposed) {
        return;
    }
    glfwDestroyWindow(m_glfwWindow);
    m_glfwWindow = nullptr;
    m_disposed = true;
    // remove self from global window list.
    auto iter = std::remove_if(s_windows.begin(), s_windows.end(),
        [](Window::Instance e) -> bool {
            return e->m_glfwWindow == nullptr;
        });
    s_windows.erase(iter, s_windows.end());
}
std::vector<Window::Instance> Window::getWindows()
{
    return s_windows;
}
// private
Window::Window(GLFWwindow* glfwWindow)
    : m_glfwWindow(glfwWindow)
    , m_disposed(false)
{
}
}