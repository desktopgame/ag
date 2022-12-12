#include <ag/Engine.hpp>
#include <ag/Looper.hpp>
#include <ag/Window.hpp>
#include <ag/easy/App.hpp>

namespace ag::easy {
App::App(int argc, char* argv[])
    : m_engine(ag::Engine::getInstance()->startup(argc, argv))
    , m_renderer()
{
}
App::~App()
{
    m_engine->shutdown();
}
int App::main(int width, int height, bool resizable, const std::string& title)
{
    auto looper = m_engine->getLooper();
    auto window = ag::Window::create(width, height, resizable, title);
    window->makeContextCurrent();
    m_renderer = std::make_shared<ag::Renderer>();
    this->start(window, m_renderer);
    // start main loop.
    while (looper->nextLoop()) {
        while (looper->nextWindow()) {
            auto w = looper->acquire();
            m_renderer->resize(w->getSize());
            this->update(w, m_renderer);
            looper->release();
        }
    }
    return 0;
}
}