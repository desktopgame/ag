#include <ag/Engine.hpp>
#include <ag/Looper.hpp>
#include <ag/Window.hpp>
#include <ag/native/glfw.hpp>

int main(int argc, char* argv[])
{
    auto engine = ag::Engine::getInstance()->startup(argc, argv);
    auto looper = engine->getLooper();
    ag::Window::create(1280, 720, false, "Window");
    while (looper->isRunnable()) {
        looper->run();
    }
    return 0;
}