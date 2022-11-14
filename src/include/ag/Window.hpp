#pragma once
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
    void dispose();
    bool isDisposed() const;
    static const std::vector<Instance>& getWindows();

private:
    Window(GLFWwindow* glfwWindow);
    static std::vector<Instance> s_windows;
    GLFWwindow* m_glfwWindow;
    bool m_disposed;
};
}