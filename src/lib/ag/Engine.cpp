#include <ag/Engine.hpp>
#include <ag/ImageIO.hpp>
#include <ag/Looper.hpp>
#include <ag/Window.hpp>
#include <ag/native/glfw.hpp>
#include <stdexcept>

#if AG_OPEN_GL
#include <ag/graphics/ogl/OglGraphicsDriver.hpp>
#endif

#if AG_METAL
#include <ag/graphics/mtl/MtlGraphicsDriver.hpp>
#endif

namespace ag {
std::mutex Engine::s_mutex;
Engine::Instance Engine::s_instance = nullptr;

Engine::~Engine()
{
    shutdown();
}

Engine::Instance Engine::getInstance()
{
    std::lock_guard<std::mutex> lock(s_mutex);
    if (!s_instance) {
        s_instance = Engine::Instance(new Engine());
    }
    return s_instance;
}

void Engine::require()
{
    if (!s_instance || !s_instance->m_started) {
        throw std::logic_error("Engine is not exist.");
    }
}

Engine::Instance Engine::startup(int argc, char* argv[])
{
    // startup runs a only at first call.
    if (m_started) {
        return nullptr;
    }
    m_started = true;
    // initialize glfw system.
    int glfwStatus = glfwInit();
    if (glfwStatus == GLFW_FALSE) {
        return nullptr;
    }
    // initialize freeimage system.
    ImageIO::initialize();
    return s_instance;
}

void Engine::shutdown()
{
    if (!m_started) {
        return;
    }
    // destroy all window.
    std::vector<Window::Instance> windows = Window::getWindows();
    std::for_each(windows.begin(), windows.end(), std::bind(&Window::dispose, std::placeholders::_1));
    // terminalte glfw.
    glfwTerminate();
    s_instance = nullptr;
    // terminalte freeimage.
    ImageIO::destroy();
}
std::shared_ptr<Looper> Engine::getLooper() const
{
    return m_looper;
}
std::shared_ptr<IGraphicsDriver> Engine::getGraphicsDriver() const
{
    return m_graphicsDriver;
}

// private
Engine::Engine()
    : m_started(false)
    , m_looper(std::make_shared<Looper>())
    , m_graphicsDriver()
{
#if AG_OPEN_GL
    m_graphicsDriver = std::make_shared<OglGraphicsDriver>();
#elif AG_METAL
    m_graphicsDriver = std::make_shared<MtlGraphicsDriver>();
#endif
}
}