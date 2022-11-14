#include <ag/Engine.hpp>
#include <ag/Looper.hpp>
#include <ag/Window.hpp>
#include <ag/native/glfw.hpp>

int main(int argc, char* argv[])
{
    auto engine = ag::Engine::getInstance()->startup(argc, argv);
    auto looper = engine->getLooper();
    auto window = ag::Window::create(1280, 720, false, "");
    auto window2 = ag::Window::create(1280, 720, false, "");
    while (looper->isRunnable()) {
        looper->run();
    }
    return 0;
}