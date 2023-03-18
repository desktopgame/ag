#include <ag/Engine.hpp>
#include <ag/Looper.hpp>
#include <ag/Window.hpp>
#include <ag/easy/App.hpp>
#include <ag/graphics/FontFactory.hpp>
#include <ag/graphics/IGraphicsDevice.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/ImageLoader.hpp>
#include <ag/graphics/Model.hpp>

namespace ag::easy {
App::App(int argc, char* argv[])
    : m_engine(ag::Engine::getInstance()->startup(argc, argv))
    , m_renderer()
    , m_textureMap()
    , m_fontMap()
    , m_modelMap()
    , m_inputSystem()
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
    m_inputSystem = std::make_shared<InputSystem>(window);
    this->start(window, m_inputSystem->getInputState(), m_renderer);
    // start main loop.
    while (looper->nextLoop()) {
        while (looper->nextWindow()) {
            auto w = looper->acquire();
            m_renderer->resize(w->getSize());
            m_inputSystem->scanEvents();
            this->update(w, m_inputSystem->getInputState(), m_renderer);
            looper->release();
        }
    }
    m_renderer = nullptr;
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
std::shared_ptr<FontMap> App::loadFontMap(const std::string& file)
{
    if (!m_fontMap.count(file)) {
        m_fontMap.insert_or_assign(file, ag::FontFactory::getInstance()->load(file));
    }
    return m_fontMap.at(file);
}
std::shared_ptr<Model> App::loadModel(const std::string& file)
{
    if (!m_modelMap.count(file)) {
        m_modelMap.insert_or_assign(file, Model::loadFromFile(file));
    }
    return m_modelMap.at(file);
}
}