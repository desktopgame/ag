#include <ag/Engine.hpp>
#include <ag/Looper.hpp>
#include <ag/Window.hpp>
#include <ag/graphics/Renderer.hpp>

int main(int argc, char* argv[])
{
    auto engine = ag::Engine::getInstance()->startup(argc, argv);
    auto looper = engine->getLooper();
    ag::Window::create(1280, 720, false, "Window");
    ag::Renderer* renderer = nullptr;
    while (looper->nextLoop()) {
        while (looper->nextWindow()) {
            auto window = looper->acquire();
            if (!renderer) {
                renderer = new ag::Renderer();
            }
            renderer->resize(window->getSize());
            renderer->drawCircle(glm::vec2(), glm::vec2(100, 100), glm::vec4(1, 1, 0, 0));
            looper->release();
        }
    }
    delete renderer;
    return 0;
}