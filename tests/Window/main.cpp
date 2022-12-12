#include <ag/agOne.hpp>

int main(int argc, char* argv[])
{
    auto engine = ag::Engine::getInstance()->startup(argc, argv);
    auto looper = engine->getLooper();
    auto window = ag::Window::create(1280, 720, false, "Window");
    auto fontMap = ag::FontFactory::getInstance()->load("testdata/fonts/NotoSansJP-Regular.otf");
    window->makeContextCurrent();
    // create renderer.
    auto renderer = new ag::Renderer();
    renderer->setFontMap(fontMap);
    // load texture.
    ag::Image img;
    ag::ImageLoader::load("testdata/textures/ghicon.png", img);
    ag::ITexture::Instance texture = engine->getGraphicsDriver()->getGraphicsDevice()->newTexture(img.width, img.height, img.getData());
    // start main loop.
    while (looper->nextLoop()) {
        while (looper->nextWindow()) {
            auto window = looper->acquire();
            renderer->resize(window->getSize());
            renderer->fillCircle(glm::vec2(), glm::vec2(100, 100), glm::vec4(1, 1, 0, 1));
            renderer->fillRect(glm::vec2(0, 100), glm::vec2(100, 100), glm::vec4(1, 0, 0, 1));
            renderer->drawRect(glm::vec2(100, 0), glm::vec2(100, 100), glm::vec4(1, 1, 0, 1));
            renderer->drawCircle(glm::vec2(100, 100), glm::vec2(100, 100), glm::vec4(1, 0, 0, 1));
            renderer->drawTexture(glm::vec2(200, 0), texture);
            renderer->fillRect(glm::vec2(0, 0), glm::vec2(200, 200), glm::vec4(1, 0, 0, 0.5f));
            renderer->fillRect(glm::vec2(500, 500), glm::vec2(200, 200), glm::vec4(1, 0, 0, 0.5f));

            glm::vec2 helloTextPos = glm::vec2(600, 600);
            renderer->drawString(helloTextPos, 20, u"こんにちは世界", glm::vec4(1, 1, 1, 1));
            helloTextPos.x += renderer->measureString(20, u"こんにちは世界").x;
            renderer->drawString(helloTextPos, 20, u"さようなら", glm::vec4(1, 0, 1, 1));
            looper->release();
        }
    }
    delete renderer;
    return 0;
}