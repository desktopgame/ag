#include <ag/agOne.hpp>

int main(int argc, char* argv[])
{
    auto engine = ag::Engine::getInstance()->startup(argc, argv);
    auto looper = engine->getLooper();
    ag::Window::create(1280, 720, false, "Window");
    ag::Renderer* renderer = nullptr;
    ag::Image img;
    ag::ImageLoader::load("testdata/ghicon.png", img);
    ag::ITexture::Instance texture = nullptr;
    while (looper->nextLoop()) {
        while (looper->nextWindow()) {
            auto window = looper->acquire();
            if (!texture) {
                texture = engine->getGraphicsDriver()->getGraphicsDevice()->newTexture(img.width, img.height, img.getData());
            }
            if (!renderer) {
                renderer = new ag::Renderer();
            }
            renderer->resize(window->getSize());
            renderer->fillCircle(glm::vec2(), glm::vec2(100, 100), glm::vec4(1, 1, 0, 1));
            renderer->fillRect(glm::vec2(0, 100), glm::vec2(100, 100), glm::vec4(1, 0, 0, 1));
            renderer->drawRect(glm::vec2(100, 0), glm::vec2(100, 100), glm::vec4(1, 1, 0, 1));
            renderer->drawCircle(glm::vec2(100, 100), glm::vec2(100, 100), glm::vec4(1, 0, 0, 1));
            renderer->drawTexture(glm::vec2(200, 0), texture);
            renderer->fillRect(glm::vec2(0, 0), glm::vec2(200, 200), glm::vec4(1, 0, 0, 0.5f));
            renderer->fillRect(glm::vec2(500, 500), glm::vec2(200, 200), glm::vec4(1, 0, 0, 0.5f));
            looper->release();
        }
    }
    delete renderer;
    return 0;
}