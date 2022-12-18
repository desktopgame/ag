#include <ag/easy/App.hpp>
#include <ag/ui/BoxLayout.hpp>
#include <ag/ui/BoxLayoutParameter.hpp>
#include <ag/ui/Button.hpp>
#include <ag/ui/Container.hpp>
#include <ag/ui/EventQueue.hpp>
#include <ag/ui/Frame.hpp>
#include <ag/ui/Label.hpp>
#include <ag/ui/Panel.hpp>
#include <ag/ui/TextField.hpp>

class MyApp : public ag::easy::App {
public:
    MyApp(int argc, char* argv[])
        : App(argc, argv)
    {
    }
    void start(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
        auto formRoot = std::make_shared<agui::Panel>(std::make_shared<agui::BoxLayout>(agui::Orientation::Vertical));
        formRoot->addComponent(createForm(u"年齢"), nullptr);
        formRoot->addComponent(createForm(u"名前"), nullptr);
        formRoot->addComponent(createForm(u"身長"), nullptr);
        formRoot->addComponent(createForm(u"体重"), nullptr);
        formRoot->addComponent(std::make_shared<agui::Button>(u"送信"), nullptr);
        formRoot->setOpaque(true);
        // create window
        m_frame = std::make_shared<agui::Frame>(w);
        m_frame->setFont(agui::Font { loadFontMap("testdata/fonts/NotoSansJP-Regular.otf"), 16 });
        m_frame->addComponent(formRoot, std::make_shared<agui::BorderLayoutParameter>(agui::BorderPosition::Center));
    }
    void update(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
        m_frame->validate();
        m_frame->update(r);
        agui::EventQueue::getInstance()->dispatch();
    }
    std::shared_ptr<agui::Panel> createForm(const std::u16string& text)
    {
        auto hbox = std::make_shared<agui::Panel>(std::make_shared<agui::BoxLayout>(agui::Orientation::Horizontal));
        hbox->addComponent(std::make_shared<agui::Label>(text), nullptr);
        hbox->addComponent(std::make_shared<agui::TextField>(), nullptr);
        return hbox;
    }

private:
    std::shared_ptr<agui::Frame> m_frame;
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(600, 400, true, "UI_Box");
}