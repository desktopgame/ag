#include <ag/easy/App.hpp>

class MyApp : public ag::easy::App {
public:
    MyApp(int argc, char* argv[])
        : App(argc, argv)
    {
    }
    void start(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
        r->setFontMap(loadFontMap("testdata/fonts/NotoSansJP-Regular.otf"));
        loadTexture("testdata/textures/ghicon.png");
    }
    void update(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
        r->fillCircle(glm::vec2(), glm::vec2(100, 100), glm::vec4(1, 1, 0, 1));
        r->fillRect(glm::vec2(0, 100), glm::vec2(100, 100), glm::vec4(1, 0, 0, 1));
        r->drawRect(glm::vec2(100, 0), glm::vec2(100, 100), glm::vec4(1, 1, 0, 1));
        r->drawCircle(glm::vec2(100, 100), glm::vec2(100, 100), glm::vec4(1, 0, 0, 1));
        r->drawTexture(glm::vec2(200, 0), loadTexture("testdata/textures/ghicon.png"), glm::vec4(1, 1, 1, 1));
        r->fillRect(glm::vec2(0, 0), glm::vec2(200, 200), glm::vec4(1, 0, 0, 0.5f));
        r->fillRect(glm::vec2(500, 500), glm::vec2(200, 200), glm::vec4(1, 0, 0, 0.5f));

        glm::vec2 helloTextPos = glm::vec2(600, 600);
        r->drawString(helloTextPos, 20, u"こんにちは世界", glm::vec4(1, 1, 1, 1));
        helloTextPos.x += r->measureString(20, u"こんにちは世界").x;
        r->drawString(helloTextPos, 20, u"さようなら", glm::vec4(1, 0, 1, 1));
    }

private:
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(1280, 720, false, "Window");
}