#pragma once
#include <ag/Window.hpp>
#include <ag/graphics/Renderer.hpp>
#include <memory>
#include <string>

namespace ag {
class Engine;
}

namespace ag::easy {
class App {
public:
    explicit App(int argc, char* argv[]);
    virtual ~App();

    int main(int width, int height, bool resizable, const std::string& title);

    virtual void start(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r) = 0;
    virtual void update(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r) = 0;

private:
    std::shared_ptr<ag::Engine> m_engine;
    std::shared_ptr<ag::Renderer> m_renderer;
};
}