#include <ag/Engine.hpp>
#include <ag/Looper.hpp>
#include <ag/Window.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/IRenderFunction.hpp>
#include <ag/graphics/RenderPass.hpp>
#include <ag/native/glfw.hpp>
#include <algorithm>

namespace ag {
Looper::Looper()
    : m_windows()
    , m_cursor()
    , m_use(false)
    , m_at(-1)
    , m_timeNow(0.0)
    , m_timeLast(0.0)
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
    Engine::getInstance()->getGraphicsDriver()->getRenderFunction()->clear(m_cursor);
    return m_cursor;
}

void Looper::release()
{
    Engine::require();
    Engine::getInstance()->getGraphicsDriver()->getRenderFunction()->present(m_cursor);
    m_cursor->swapBuffers();
    glfwPollEvents();
    m_use = false;
}

bool Looper::nextLoop()
{
    Engine::require();
    m_windows = Window::getWindows();
    m_at = 0;
    m_timeNow = glfwGetTime();
    return !m_windows.empty();
}

bool Looper::nextWindow()
{
    Engine::require();
    bool ret = m_at < static_cast<int>(m_windows.size());
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
        m_timeLast = m_timeNow;
    }
    return ret;
}

float Looper::deltaTime() const
{
    double diff = m_timeNow - m_timeLast;
    if (diff < 0.0f) {
        diff = 0.0f;
    }
    return static_cast<float>(diff);
}
}