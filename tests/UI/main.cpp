#include <ag/easy/App.hpp>
#include <ag/ui/BoxLayout.hpp>
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
        m_root = std::make_shared<agui::Panel>(std::make_shared<agui::BoxLayout>(agui::Orientation::Horizontal));
        m_root->setFont(agui::Font { loadFontMap("testdata/fonts/NotoSansJP-Regular.otf"), 12 });
        auto vbox = std::make_shared<agui::Panel>(std::make_shared<agui::BoxLayout>(agui::Orientation::Vertical));
        auto h1 = std::make_shared<agui::Panel>(std::make_shared<agui::BoxLayout>(agui::Orientation::Horizontal));
        h1->setBackground(glm::vec4 { 1, 0, 0, 1 });
        layoutPanel(h1, { 1, 0, 0, 1 }, { 0, 1, 0, 1 });
        auto h2 = std::make_shared<agui::Panel>(std::make_shared<agui::BoxLayout>(agui::Orientation::Horizontal));
        h2->setBackground(glm::vec4 { 0, 1, 0, 1 });
        layoutPanel(h2, { 1, 0, 1, 1 }, { 0, 1, 1, 1 });
        auto h3 = std::make_shared<agui::Panel>(std::make_shared<agui::BoxLayout>(agui::Orientation::Horizontal));
        h3->setBackground(glm::vec4 { 0, 0, 1, 1 });
        layoutPanel(h3, { 1, 0, 0, 1 }, { 1, 1, 0, 1 });
        vbox->addComponent(h1, std::make_shared<agui::BoxLayoutParameter>(0));
        vbox->addComponent(h2, std::make_shared<agui::BoxLayoutParameter>(0));
        vbox->addComponent(h3, std::make_shared<agui::BoxLayoutParameter>(0));
        auto fill = std::make_shared<agui::Panel>(nullptr);
        fill->setBackground({ 1, 0, 0, 1 });
        m_root->addComponent(vbox, std::make_shared<agui::BoxLayoutParameter>(0));
        m_root->addComponent(fill, std::make_shared<agui::BoxLayoutParameter>(0));
    }
    void update(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
        m_root->setBounds(agui::Rect { { 0, 0 }, { w->getSize() } });
        m_root->doLayoutTree();
        m_root->update(r);
    }
    void layoutPanel(std::shared_ptr<agui::Panel> p, glm::vec4 c1, glm::vec4 c2)
    {
        auto sub1 = std::make_shared<agui::Button>(u"こんにちは");
        sub1->setBackground(c1);
        auto sub2 = std::make_shared<agui::Panel>(nullptr);
        sub2->setBackground(c2);
        p->addComponent(sub1, std::make_shared<agui::BoxLayoutParameter>(1));
        p->addComponent(sub2, std::make_shared<agui::BoxLayoutParameter>(3));
    }

private:
    std::shared_ptr<agui::Container> m_root;
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(1280, 720, true, "UI");
}