#include <ag/easy/App.hpp>
#include <ag/ui/BorderLayout.hpp>
#include <ag/ui/BorderLayoutParameter.hpp>
#include <ag/ui/BoxLayout.hpp>
#include <ag/ui/BoxLayoutParameter.hpp>
#include <ag/ui/Button.hpp>
#include <ag/ui/Container.hpp>
#include <ag/ui/Frame.hpp>
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
        auto root = std::make_shared<agui::Panel>(std::make_shared<agui::BorderLayout>());
        setBorderLayout(root, 100, true);
        // create window
        m_frame = std::make_shared<agui::Frame>(w);
        m_frame->setFont(agui::Font { loadFontMap("testdata/fonts/NotoSansJP-Regular.otf"), 16 });
        m_frame->addComponent(root, std::make_shared<agui::BorderLayoutParameter>(agui::BorderPosition::Center));
    }
    void update(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
        m_frame->validate();
        m_frame->update(r);
    }
    void setBorderLayout(std::shared_ptr<agui::Container> parent, int prefSize, bool child)
    {
        auto center = std::make_shared<agui::Panel>(nullptr);
        center->setOpaque(true);
        parent->addComponent(center, std::make_shared<agui::BorderLayoutParameter>(agui::BorderPosition::Center));

        auto top = std::make_shared<agui::Panel>(nullptr);
        top->setPreferredSize({ prefSize, prefSize });
        top->setBackground({ 1, 0, 0, 1 });
        top->setOpaque(true);
        parent->addComponent(top, std::make_shared<agui::BorderLayoutParameter>(agui::BorderPosition::Top));

        auto bottom = std::make_shared<agui::Panel>(nullptr);
        bottom->setPreferredSize({ prefSize, prefSize });
        bottom->setBackground({ 1, 1, 0, 1 });
        bottom->setOpaque(true);
        parent->addComponent(bottom, std::make_shared<agui::BorderLayoutParameter>(agui::BorderPosition::Bottom));

        auto left = std::make_shared<agui::Panel>(nullptr);
        left->setPreferredSize({ prefSize, prefSize });
        left->setBackground({ 0, 1, 1, 1 });
        left->setOpaque(true);
        parent->addComponent(left, std::make_shared<agui::BorderLayoutParameter>(agui::BorderPosition::Left));

        auto right = std::make_shared<agui::Panel>(nullptr);
        right->setPreferredSize({ prefSize, prefSize });
        right->setBackground({ 1, 1, 1, 1 });
        right->setOpaque(true);
        parent->addComponent(right, std::make_shared<agui::BorderLayoutParameter>(agui::BorderPosition::Right));
    }

private:
    std::shared_ptr<agui::Frame> m_frame;
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(1280, 720, true, "UI_Border");
}