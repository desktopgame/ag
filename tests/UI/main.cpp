#include <ag/easy/App.hpp>
#include <ag/ui/Button.hpp>
#include <ag/ui/HBox.hpp>
#include <ag/ui/Label.hpp>
#include <ag/ui/Panel.hpp>
#include <ag/ui/VBox.hpp>

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
    }

private:
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(1280, 720, true, "Window");
}