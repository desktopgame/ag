#include <ag/easy/App.hpp>
#include <ag/ui/BoxLayoutManager.hpp>
#include <ag/ui/BoxLayoutParameter.hpp>
#include <ag/ui/Button.hpp>
#include <ag/ui/Container.hpp>
#include <ag/ui/Label.hpp>
#include <ag/ui/Panel.hpp>

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
        m_root = std::make_shared<agui::Panel>(std::make_shared<agui::BoxLayoutManager>(agui::Orientation::Horizontal));
        auto p1 = std::make_shared<agui::Panel>(nullptr);
        p1->setBackground(glm::vec4 { 1, 0, 0, 1 });
        auto p2 = std::make_shared<agui::Panel>(nullptr);
        p2->setBackground(glm::vec4 { 0, 1, 0, 1 });
        auto p3 = std::make_shared<agui::Panel>(nullptr);
        p3->setBackground(glm::vec4 { 0, 0, 1, 1 });
        m_root->addComponent(p1, std::make_shared<agui::BoxLayoutParameter>(0));
        m_root->addComponent(p2, std::make_shared<agui::BoxLayoutParameter>(0));
        m_root->addComponent(p3, std::make_shared<agui::BoxLayoutParameter>(0));
    }
    void update(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
        m_root->setBounds(agui::Rect { { 0, 0 }, { 1280, 720 } });
        m_root->doLayoutTree(agui::Rect { { 0, 0 }, { 1280, 720 } });
        m_root->update(r);
    }

private:
    std::shared_ptr<agui::Container> m_root;
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(1280, 720, true, "Window");
}