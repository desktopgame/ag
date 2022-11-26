#include <ag/Engine.hpp>
#include <ag/Looper.hpp>
#include <ag/Window.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/native/glfw.hpp>
#include <algorithm>

namespace ag {
Looper::Looper()
    : m_windows()
    , m_cursor()
    , m_use(false)
    , m_at(-1)
{
}

std::shared_ptr<Window> Looper::acquire()
{
    Engine::require();
    if (!m_cursor || m_use) {
        return nullptr;
    }
    m_use = true;
    m_cursor->makeContextCurrent();
    Engine::getInstance()->getGraphicsDriver()->useContextExtension();
    return m_cursor;
}

void Looper::release()
{
    Engine::require();
    m_cursor->swapBuffers();
    glfwPollEvents();
    m_use = false;
    m_at++;
}

bool Looper::nextLoop()
{
    Engine::require();
    m_windows = Window::getWindows();
    m_at = 0;
    return !m_windows.empty();
}

bool Looper::nextWindow()
{
    Engine::require();
    bool ret = m_at < m_windows.size();
    if (ret) {
        m_cursor = m_windows.at(m_at);
        m_at++;
    } else {
        for (auto window : m_windows) {
            if (window->shouldClose()) {
                window->dispose();
            }
        }
        m_at = -1;
        m_cursor = nullptr;
    }
    return ret;
}
}