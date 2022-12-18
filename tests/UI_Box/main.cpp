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
        auto rootBox = std::make_shared<agui::Panel>(std::make_shared<agui::BoxLayout>(agui::Orientation::Horizontal));
        auto vbox1 = createVBox();
        auto vbox2 = createVBox();
        vbox2->setBackground({ 1, 0, 0, 1 });
        rootBox->setOpaque(true);
        rootBox->addComponent(vbox1, nullptr);
        rootBox->addComponent(vbox2, nullptr);
        // create window
        m_frame = std::make_shared<agui::Frame>(w);
        m_frame->setFont(agui::Font { loadFontMap("testdata/fonts/NotoSansJP-Regular.otf"), 16 });
        m_frame->addComponent(rootBox, std::make_shared<agui::BorderLayoutParameter>(agui::BorderPosition::Center));
    }
    void update(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
        m_frame->validate();
        m_frame->update(r);
        agui::EventQueue::getInstance()->dispatch();
    }
    std::shared_ptr<agui::Panel> createVBox()
    {
        auto vbox = std::make_shared<agui::Panel>(std::make_shared<agui::BoxLayout>(agui::Orientation::Vertical));
        vbox->setOpaque(true);
        vbox->addComponent(createHBox(), nullptr);
        vbox->addComponent(createHBox(), nullptr);
        vbox->addComponent(createHBox(), nullptr);
        return vbox;
    }
    std::shared_ptr<agui::Panel> createHBox()
    {
        auto hbox = std::make_shared<agui::Panel>(std::make_shared<agui::BoxLayout>(agui::Orientation::Horizontal));
        hbox->addComponent(std::make_shared<agui::Button>(u"ボタン"), nullptr);
        hbox->addComponent(std::make_shared<agui::TextField>(), nullptr);
        hbox->addComponent(std::make_shared<agui::Label>(u"テキスト２"), nullptr);
        return hbox;
    }

private:
    std::shared_ptr<agui::Frame> m_frame;
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(1280, 720, true, "UI_Box");
}