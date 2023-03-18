#pragma once
#include <ag/Window.hpp>
#include <ag/graphics/Renderer.hpp>
#include <ag/input/InputSystem.hpp>
#include <memory>
#include <string>
#include <unordered_map>

namespace ag {
class Engine;
class ITexture;
class Model;
class FontMap;
}

namespace ag::easy {
class App {
public:
    explicit App(int argc, char* argv[]);
    virtual ~App();

    int main(int width, int height, bool resizable, const std::string& title);

    virtual void start(const ag::Window::Instance& window, const ag::InputState& input, const ag::Renderer::Instance& renderer) = 0;
    virtual void update(const ag::Window::Instance& window, const ag::InputState& input, const ag::Renderer::Instance& renderer) = 0;

protected:
    std::shared_ptr<ITexture> loadTexture(const std::string& file);
    std::shared_ptr<FontMap> loadFontMap(const std::string& file);
    std::shared_ptr<Model> loadModel(const std::string& file);

private:
    std::shared_ptr<ag::Engine> m_engine;
    std::shared_ptr<ag::Renderer> m_renderer;
    std::unordered_map<std::string, std::shared_ptr<ITexture>> m_textureMap;
    std::unordered_map<std::string, std::shared_ptr<FontMap>> m_fontMap;
    std::unordered_map<std::string, std::shared_ptr<Model>> m_modelMap;
    std::shared_ptr<InputSystem> m_inputSystem;
};
}