#pragma once
#include <ag/Window.hpp>
#include <ag/graphics/Renderer.hpp>
#include <memory>
#include <string>
#include <unordered_map>

namespace ag {
class Engine;
class ITexture;
class FontMap;
}

namespace ag::easy {
class App {
public:
    explicit App(int argc, char* argv[]);
    virtual ~App();

    int main(int width, int height, bool resizable, const std::string& title);

    virtual void start(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r) = 0;
    virtual void update(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r) = 0;

protected:
    std::shared_ptr<ITexture> loadTexture(const std::string& file);
    std::shared_ptr<FontMap> loadFontMap(const std::string& file);

private:
    std::shared_ptr<ag::Engine> m_engine;
    std::shared_ptr<ag::Renderer> m_renderer;
    std::unordered_map<std::string, std::shared_ptr<ITexture>> m_textureMap;
    std::unordered_map<std::string, std::shared_ptr<FontMap>> m_fontMap;
};
}