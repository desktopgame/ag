#include <ag/Engine.hpp>
#include <ag/Looper.hpp>
#include <ag/Window.hpp>
#include <ag/easy/App.hpp>
#include <ag/graphics/FontFactory.hpp>
#include <ag/graphics/IGraphicsDevice.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/ImageLoader.hpp>

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
// protected
std::shared_ptr<ITexture> App::loadTexture(const std::string& file)
{
    if (!m_textureMap.count(file)) {
        ag::Image img;
        ag::ImageLoader::load(file, img);
        m_textureMap.insert_or_assign(file, Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice()->newTexture(img.width, img.height, img.getData()));
    }
    return m_textureMap.at(file);
}
std::shared_ptr<FontMap> App::loadFont(const std::string& file)
{
    if (!m_fontMap.count(file)) {
        m_fontMap.insert_or_assign(file, ag::FontFactory::getInstance()->load(file));
    }
    return m_fontMap.at(file);
}
}