#include <ag/Engine.hpp>
#include <ag/Window.hpp>
#include <ag/native/glfw.hpp>

int main(int argc, char* argv[])
{
    auto engine = ag::Engine::getInstance()->startup(argc, argv);
    auto window = ag::Window::create(1280, 720, false, "");
    window->makeContextCurrent();
    while (!window->shouldClose()) {
        glfwPollEvents();
    }
    return 0;
}