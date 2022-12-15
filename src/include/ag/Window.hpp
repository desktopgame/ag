#pragma once
#include <ag/native/glm.hpp>
#include <ag/native/metal.hpp>
#include <memory>
#include <string>
#include <vector>

struct GLFWwindow;

namespace ag {
class Window : public std::enable_shared_from_this<Window> {
public:
    using Instance = std::shared_ptr<Window>;

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
    glm::ivec2 getMousePosition() const;

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

    static std::vector<Instance> s_windows;
    GLFWwindow* m_glfwWindow;
    std::string m_title;
    glm::vec3 m_clearColor;
    bool m_disposed;
#if AG_METAL
    CA::MetalLayer* m_metalLayer;
#endif
};
}