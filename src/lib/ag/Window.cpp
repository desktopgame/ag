#include <ag/Engine.hpp>
#include <ag/Window.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/mtl/MtlGraphicsDriver.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
std::vector<Window::Instance> Window::s_windows;

Window::Instance Window::create(int width, int height, bool resizable, const std::string& title)
{
    Engine::require();
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_RESIZABLE, resizable);
    Engine::getInstance()->getGraphicsDriver()->useWindowHint();
    // create window instance.
    GLFWwindow* glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    Window::Instance window = Window::Instance(new Window(glfwWindow, title));
    Window::s_windows.emplace_back(window);
    // link metal layer.
#if AG_METAL
    window->m_metalLayer = CA::MetalLayer::alloc()->init();
    //window->m_metalLayer->setDevice(m_device);
    std::static_pointer_cast<MtlGraphicsDriver>(Engine::getInstance()->getGraphicsDriver())->useDevice(window->m_metalLayer);
    window->m_metalLayer->setOpaque(true);
    NS::Window* nsWindow = NS::Window::bridgingCast(getCocoaWindow(glfwWindow));
    NS::View* contentView = nsWindow->contentView();
    contentView->setLayer(window->m_metalLayer);
    contentView->setWantsLayer(true);
#endif
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
void Window::swapBuffers()
{
#ifdef AG_OPEN_GL
    glfwSwapBuffers(m_glfwWindow);
#endif
}
void Window::setTitle(const std::string& title)
{
    m_title = title;
    glfwSetWindowTitle(m_glfwWindow, title.c_str());
}
std::string Window::getTitle() const
{
    return m_title;
}
void Window::setSize(const glm::ivec2& size)
{
    glfwSetWindowSize(m_glfwWindow, size.x, size.y);
}
glm::ivec2 Window::getSize() const
{
    glm::ivec2 v;
    glfwGetWindowSize(m_glfwWindow, &v.x, &v.y);
    return v;
}
void Window::setPosition(const glm::ivec2& position)
{
    glfwSetWindowPos(m_glfwWindow, position.x, position.y);
}
glm::ivec2 Window::getPosition() const
{
    glm::ivec2 v;
    glfwGetWindowPos(m_glfwWindow, &v.x, &v.y);
    return v;
}
void Window::setClearColor(const glm::vec3& clearColor)
{
    m_clearColor = clearColor;
}
glm::vec3 Window::getClearColor() const { return m_clearColor; }
glm::ivec2 Window::getFrameBufferSize() const
{
    glm::ivec2 v;
    glfwGetFramebufferSize(m_glfwWindow, &v.x, &v.y);
    return v;
}
glm::ivec2 Window::getMousePosition() const
{
    double x, y;
    glfwGetCursorPos(m_glfwWindow, &x, &y);
    return { static_cast<int>(x), static_cast<int>(y) };
}
#ifdef AG_METAL
CA::MetalDrawable* Window::nextDrawable()
{
    return m_metalLayer->nextDrawable();
}
#endif
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
bool Window::isDisposed() const
{
    return m_disposed;
}
const std::vector<Window::Instance>& Window::getWindows()
{
    return s_windows;
}
// private
Window::Window(GLFWwindow* glfwWindow, const std::string& title)
    : m_glfwWindow(glfwWindow)
    , m_title(title)
    , m_clearColor(0.f, 0.f, 0.f)
    , m_disposed(false)
#if AG_METAL
    , m_metalLayer(nullptr)
#endif
{
}
}