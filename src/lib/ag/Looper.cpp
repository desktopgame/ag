#include <ag/Engine.hpp>
#include <ag/Looper.hpp>
#include <ag/Window.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/native/glfw.hpp>
#include <algorithm>

namespace ag {
Looper::Looper()
{
}

void Looper::run()
{
    Engine::require();
    auto windows = Window::getWindows();
    for (Window::Instance window : windows) {
        window->makeContextCurrent();
        Engine::getInstance()->getGraphicsDriver()->useContextExtension();
        glfwPollEvents();
        if (window->shouldClose()) {
            window->dispose();
        }
    }
}

bool Looper::isRunnable() const
{
    return !Window::getWindows().empty();
}
}