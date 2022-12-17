#include <ag/easy/App.hpp>
#include <ag/ui/BorderLayout.hpp>
#include <ag/ui/BorderLayoutParameter.hpp>
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
        m_root = std::make_shared<agui::Panel>(std::make_shared<agui::BorderLayout>());
        m_root->setFont(agui::Font { loadFontMap("testdata/fonts/NotoSansJP-Regular.otf"), 16 });

        auto center = std::make_shared<agui::Panel>(nullptr);
        center->setOpaque(true);
        m_root->addComponent(center, std::make_shared<agui::BorderLayoutParameter>(agui::BorderPosition::Center));

        int prefSize = 200;

        auto top = std::make_shared<agui::Panel>(nullptr);
        top->setPreferredSize({ 0, prefSize });
        top->setBackground({ 1, 0, 0, 1 });
        top->setOpaque(true);
        m_root->addComponent(top, std::make_shared<agui::BorderLayoutParameter>(agui::BorderPosition::Top));

        auto bottom = std::make_shared<agui::Panel>(nullptr);
        bottom->setPreferredSize({ 0, prefSize });
        bottom->setBackground({ 1, 1, 0, 1 });
        bottom->setOpaque(true);
        m_root->addComponent(bottom, std::make_shared<agui::BorderLayoutParameter>(agui::BorderPosition::Bottom));

        auto left = std::make_shared<agui::Panel>(nullptr);
        left->setPreferredSize({ prefSize, 0 });
        left->setBackground({ 0, 1, 1, 1 });
        left->setOpaque(true);
        m_root->addComponent(left, std::make_shared<agui::BorderLayoutParameter>(agui::BorderPosition::Left));

        auto right = std::make_shared<agui::Panel>(nullptr);
        right->setPreferredSize({ prefSize, 0 });
        right->setBackground({ 1, 1, 1, 1 });
        right->setOpaque(true);
        m_root->addComponent(right, std::make_shared<agui::BorderLayoutParameter>(agui::BorderPosition::Right));

        m_root->setBounds(agui::Rect { { 0, 0 }, { w->getSize() } });
    }
    void update(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
        m_root->validate();
        m_root->update(r);
    }
    std::shared_ptr<agui::Panel> createHBox()
    {
        auto hbox = std::make_shared<agui::Panel>(std::make_shared<agui::BoxLayout>(agui::Orientation::Horizontal));
        hbox->addComponent(std::make_shared<agui::Button>(u"ボタン"), nullptr);
        hbox->addComponent(std::make_shared<agui::Label>(u"テキスト１"), nullptr);
        hbox->addComponent(std::make_shared<agui::Label>(u"テキスト２"), nullptr);
        return hbox;
    }

private:
    std::shared_ptr<agui::Container> m_root;
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(1280, 720, true, "UI_Border");
}