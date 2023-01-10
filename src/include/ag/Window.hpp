#pragma once
#include <ag/native/glm.hpp>
#include <ag/native/metal.hpp>
#include <any>
#include <functional>
#include <memory>
#include <string>
#include <vector>

struct GLFWwindow;

namespace ag {
// callback
using KeyCallback = std::function<void(int, int, int, int)>;
using CharCallback = std::function<void(unsigned int)>;
using CharModsCallback = std::function<void(unsigned int, int)>;
using MouseButtonCallback = std::function<void(int, int, int)>;
using CursorPosCallback = std::function<void(double, double)>;
using CursorEnterCallback = std::function<void(int)>;
using ScrollCallback = std::function<void(double, double)>;
using DropCallback = std::function<void(int, const char**)>;
using WindowPosCallback = std::function<void(int, int)>;
using WindowSizeCallback = std::function<void(int, int)>;
// constant
class Window : public std::enable_shared_from_this<Window> {
public:
    using Instance = std::shared_ptr<Window>;
    static const int k_eventMouseActionPress;
    static const int k_eventMouseActionRelease;
    static const int k_eventKeyActionPress;
    static const int k_eventKeyActionRelease;

    static Instance create(int width, int height, bool resizable, const std::string& title);
    bool shouldClose() const;
    void makeContextCurrent();
    void swapBuffers();

    void setTitle(const std::string& title);
    std::string getTitle() const;
    void setSize(const glm::ivec2& size);
    glm::ivec2 getSize() const;
    void setPosition(const glm::ivec2& position);
    glm::ivec2 getPosition() const;
    void setClearColor(const glm::vec3& clearColor);
    glm::vec3 getClearColor() const;
    glm::ivec2 getFrameBufferSize() const;
    glm::ivec2 getCursorPosition() const;
    void setSurfaceObject(const std::any surfaceObject);
    std::any getSurfaceObject() const;

    void setKeyCallback(KeyCallback keyCallback);
    KeyCallback getKeyCallback() const;

    void setCharCallback(CharCallback charCallback);
    CharCallback getCharCallback() const;

    void setCharModsCallback(CharModsCallback charModsCallback);
    CharModsCallback getCharModsCallback() const;

    void setMouseButtonCallback(MouseButtonCallback mouseButtonCallback);
    MouseButtonCallback getMouseButtonCallback() const;

    void setCursorPosCallback(CursorPosCallback cursorPosCallback);
    CursorPosCallback getCursorPosCallback() const;

    void setCursorEnterCallback(CursorEnterCallback cursorEnterCallback);
    CursorEnterCallback getCursorEnterCallback() const;

    void setScrollCallback(ScrollCallback scrollCallback);
    ScrollCallback getScrollCallback() const;

    void setDropCallback(DropCallback dropCallback);
    DropCallback getDropCallback() const;

    void setWindowPosCallback(WindowPosCallback windowPosCallback);
    WindowPosCallback getWindowPosCallback() const;

    void setWindowSizeCallback(WindowSizeCallback windowSizeCallback);
    WindowSizeCallback getWindowSizeCallback() const;

#ifdef AG_METAL
    CA::MetalDrawable* nextDrawable();
#endif

    void dispose();
    bool isDisposed() const;
    static const std::vector<Instance>& getWindows();

private:
    Window(GLFWwindow* glfwWindow, const std::string& title);
    static GLFWwindow* getSharedWindow();
    static void onKey(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void onChar(GLFWwindow* window, unsigned int codepoint);
    static void onCharMods(GLFWwindow* window, unsigned int codepoint, int mods);
    static void onMouseButton(GLFWwindow* window, int button, int action, int mods);
    static void onCursorPos(GLFWwindow* window, double xpos, double ypos);
    static void onCursorEnter(GLFWwindow* window, int entered);
    static void onScroll(GLFWwindow* window, double xoffset, double yoffset);
    static void onDrop(GLFWwindow* window, int path_count, const char* paths[]);
    static void onWindowPos(GLFWwindow* window, int x, int y);
    static void onWindowSize(GLFWwindow* window, int w, int h);

    static std::vector<Instance> s_windows;
    GLFWwindow* m_glfwWindow;
    std::string m_title;
    glm::vec3 m_clearColor;
    bool m_disposed;
    std::any m_surfaceObject;

    KeyCallback m_keyCallback;
    CharCallback m_charCallback;
    CharModsCallback m_charModsCallback;
    MouseButtonCallback m_mouseButtonCallback;
    CursorPosCallback m_cursorPosCallback;
    CursorEnterCallback m_cursorEnterCallback;
    ScrollCallback m_scrollCallback;
    DropCallback m_dropCallback;
    WindowPosCallback m_windowPosCallback;
    WindowSizeCallback m_windowSizeCallback;
#if AG_METAL
    CA::MetalLayer* m_metalLayer;
#endif
};
}