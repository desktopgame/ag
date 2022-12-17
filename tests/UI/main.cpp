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
        m_root = std::make_shared<agui::Panel>(std::make_shared<agui::BoxLayout>(agui::Orientation::Vertical));
        m_root->setFont(agui::Font { loadFontMap("testdata/fonts/NotoSansJP-Regular.otf"), 12 });
        m_root->addComponent(createHBox(), nullptr);
        m_root->addComponent(createHBox(), nullptr);
        m_root->addComponent(createHBox(), nullptr);
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
        hbox->addComponent(std::make_shared<agui::Label>(u"こんにちわ１"), nullptr);
        hbox->addComponent(std::make_shared<agui::Label>(u"こんにちわ２"), nullptr);
        hbox->addComponent(std::make_shared<agui::Label>(u"こんにちわ３"), nullptr);
        return hbox;
    }

private:
    std::shared_ptr<agui::Container> m_root;
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(1280, 720, true, "UI");
}