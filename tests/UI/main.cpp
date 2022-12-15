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
        m_root = std::make_shared<agui::HBox>(std::vector<int> {});
        auto tmp = std::make_shared<agui::VBox>(std::vector<int> {});
        auto line1 = std::make_shared<agui::HBox>(std::vector<int> { 1, 2 });
        auto line2 = std::make_shared<agui::HBox>(std::vector<int> { 1, 2 });
        auto line3 = std::make_shared<agui::HBox>(std::vector<int> { 1, 2 });
        line1->addComponent(std::make_shared<agui::Button>(u"こんにちは１"));
        line1->addComponent(std::make_shared<agui::Panel>(glm::vec4 { 0.f, 1.f, 0.f, 1.f }));
        line2->addComponent(std::make_shared<agui::Label>(u"こんにちは２"));
        line2->addComponent(std::make_shared<agui::Panel>(glm::vec4 { 0.f, 1.f, 0.5f, 1.f }));
        line3->addComponent(std::make_shared<agui::Label>(u"こんにちは３"));
        line3->addComponent(std::make_shared<agui::Panel>(glm::vec4 { 0.f, 1.f, 0.f, 1.f }));
        tmp->addComponent(line1);
        tmp->addComponent(line2);
        tmp->addComponent(line3);
        m_root->addComponent(tmp);
        m_root->addComponent(std::make_shared<agui::Panel>(glm::vec4 { 0, 1, 0, 1 }));
    }
    void update(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
        m_root->doLayoutTree(agui::Rect { { 0, 0 }, w->getSize() });
        m_root->update(r);
    }

private:
    std::shared_ptr<agui::HBox> m_root;
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(1280, 720, true, "Window");
}