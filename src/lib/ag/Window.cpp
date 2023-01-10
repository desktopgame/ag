#include <ag/Engine.hpp>
#include <ag/Window.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/mtl/MtlGraphicsDriver.hpp>
#include <ag/native/glfw.hpp>
#include <algorithm>

namespace ag {
const int Window::k_eventMouseActionPress = GLFW_PRESS;
const int Window::k_eventMouseActionRelease = GLFW_RELEASE;
const int Window::k_eventKeyActionPress = GLFW_PRESS;
const int Window::k_eventKeyActionRelease = GLFW_RELEASE;
std::vector<Window::Instance> Window::s_windows;

Window::Instance Window::create(int width, int height, bool resizable, const std::string& title)
{
    Engine::require();
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_RESIZABLE, resizable);
    Engine::getInstance()->getGraphicsDriver()->useWindowHint();
    // create window instance.
    GLFWwindow* glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, getSharedWindow());
    Window* windowPtr = new Window(glfwWindow, title);
    Window::Instance window = Window::Instance(windowPtr);
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
    // event
    glfwSetWindowUserPointer(glfwWindow, windowPtr);
    glfwSetKeyCallback(glfwWindow, Window::onKey);
    glfwSetCharCallback(glfwWindow, Window::onChar);
    glfwSetCharModsCallback(glfwWindow, Window::onCharMods);
    glfwSetMouseButtonCallback(glfwWindow, Window::onMouseButton);
    glfwSetCursorPosCallback(glfwWindow, Window::onCursorPos);
    glfwSetCursorEnterCallback(glfwWindow, Window::onCursorEnter);
    glfwSetScrollCallback(glfwWindow, Window::onScroll);
    glfwSetDropCallback(glfwWindow, Window::onDrop);
    glfwSetWindowPosCallback(glfwWindow, Window::onWindowPos);
    glfwSetWindowSizeCallback(glfwWindow, Window::onWindowSize);
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
glm::ivec2 Window::getCursorPosition() const
{
    double x, y;
    glfwGetCursorPos(m_glfwWindow, &x, &y);
    return { static_cast<int>(x), static_cast<int>(y) };
}
void Window::setSurfaceObject(const std::any surfaceObject) { m_surfaceObject = surfaceObject; }
std::any Window::getSurfaceObject() const { return m_surfaceObject; }
GLFWwindow* Window::getNativeWindow() const { return m_glfwWindow; }

void Window::setKeyCallback(KeyCallback keyCallback) { m_keyCallback = keyCallback; }
KeyCallback Window::getKeyCallback() const { return m_keyCallback; }

void Window::setCharCallback(CharCallback charCallback) { m_charCallback = charCallback; }
CharCallback Window::getCharCallback() const { return m_charCallback; }

void Window::setCharModsCallback(CharModsCallback charModsCallback) { m_charModsCallback = charModsCallback; }
CharModsCallback Window::getCharModsCallback() const { return m_charModsCallback; }

void Window::setMouseButtonCallback(MouseButtonCallback mouseButtonCallback) { m_mouseButtonCallback = mouseButtonCallback; }
MouseButtonCallback Window::getMouseButtonCallback() const { return m_mouseButtonCallback; }

void Window::setCursorPosCallback(CursorPosCallback cursorPosCallback) { m_cursorPosCallback = cursorPosCallback; }
CursorPosCallback Window::getCursorPosCallback() const { return m_cursorPosCallback; }

void Window::setCursorEnterCallback(CursorEnterCallback cursorEnterCallback) { m_cursorEnterCallback = cursorEnterCallback; }
CursorEnterCallback Window::getCursorEnterCallback() const { return m_cursorEnterCallback; }

void Window::setScrollCallback(ScrollCallback scrollCallback) { m_scrollCallback = scrollCallback; }
ScrollCallback Window::getScrollCallback() const { return m_scrollCallback; }

void Window::setDropCallback(DropCallback dropCallback) { m_dropCallback = dropCallback; }
DropCallback Window::getDropCallback() const { return m_dropCallback; }

void Window::setWindowPosCallback(WindowPosCallback windowPosCallback) { m_windowPosCallback = windowPosCallback; }
WindowPosCallback Window::getWindowPosCallback() const { return m_windowPosCallback; }

void Window::setWindowSizeCallback(WindowSizeCallback windowSizeCallback) { m_windowSizeCallback = windowSizeCallback; }
WindowSizeCallback Window::getWindowSizeCallback() const { return m_windowSizeCallback; }

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
    , m_surfaceObject()
    , m_keyCallback()
    , m_charCallback()
    , m_charModsCallback()
    , m_mouseButtonCallback()
    , m_cursorPosCallback()
    , m_cursorEnterCallback()
    , m_scrollCallback()
    , m_dropCallback()
    , m_windowPosCallback()
    , m_windowSizeCallback()
#if AG_METAL
    , m_metalLayer(nullptr)
#endif
{
}
GLFWwindow* Window::getSharedWindow()
{
    if (s_windows.empty()) {
        return nullptr;
    }
    return s_windows.front()->m_glfwWindow;
}
void Window::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Window* agWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (agWindow && agWindow->m_keyCallback) {
        agWindow->m_keyCallback(key, scancode, action, mods);
    }
}
void Window::onChar(GLFWwindow* window, unsigned int codepoint)
{
    Window* agWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (agWindow && agWindow->m_charCallback) {
        agWindow->m_charCallback(codepoint);
    }
}
void Window::onCharMods(GLFWwindow* window, unsigned int codepoint, int mods)
{
    Window* agWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (agWindow && agWindow->m_charModsCallback) {
        agWindow->m_charModsCallback(codepoint, mods);
    }
}
void Window::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    Window* agWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (agWindow && agWindow->m_mouseButtonCallback) {
        agWindow->m_mouseButtonCallback(button, action, mods);
    }
}
void Window::onCursorPos(GLFWwindow* window, double xpos, double ypos)
{
    Window* agWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (agWindow && agWindow->m_cursorPosCallback) {
        agWindow->m_cursorPosCallback(xpos, ypos);
    }
}
void Window::onCursorEnter(GLFWwindow* window, int entered)
{
    Window* agWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (agWindow && agWindow->m_cursorEnterCallback) {
        agWindow->m_cursorEnterCallback(entered);
    }
}
void Window::onScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    Window* agWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (agWindow && agWindow->m_scrollCallback) {
        agWindow->m_scrollCallback(xoffset, yoffset);
    }
}
void Window::onDrop(GLFWwindow* window, int path_count, const char* paths[])
{
    Window* agWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (agWindow && agWindow->m_dropCallback) {
        agWindow->m_dropCallback(path_count, paths);
    }
}
void Window::onWindowPos(GLFWwindow* window, int x, int y)
{
    Window* agWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (agWindow && agWindow->m_windowPosCallback) {
        agWindow->m_windowPosCallback(x, y);
    }
}
void Window::onWindowSize(GLFWwindow* window, int w, int h)
{
    Window* agWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (agWindow && agWindow->m_windowSizeCallback) {
        agWindow->m_windowSizeCallback(w, h);
    }
}

}