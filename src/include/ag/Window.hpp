#pragma once
#include <ag/native/glm.hpp>
#include <memory>
#include <string>
#include <vector>

struct GLFWwindow;

namespace ag {
class Window {
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

    void dispose();
    bool isDisposed() const;
    static const std::vector<Instance>& getWindows();

private:
    Window(GLFWwindow* glfwWindow, const std::string& title);
    static std::vector<Instance> s_windows;
    GLFWwindow* m_glfwWindow;
    std::string m_title;
    glm::vec3 m_clearColor;
    bool m_disposed;
};
}