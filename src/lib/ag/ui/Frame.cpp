#include <ag/ui/EventQueue.hpp>
#include <ag/ui/Frame.hpp>
#include <ag/ui/MouseEvent.hpp>

namespace agui {
Frame::Frame(const ag::Window::Instance& window)
    : Container()
    , m_window(window)
{
    window->setWindowSizeCallback([&](int w, int h) -> void {
        setBounds(Rect { { 0, 0 }, { w, h } });
    });
    window->setCursorPosCallback([&](double xpos, double ypos) -> void {
        int ix = static_cast<int>(xpos);
        int iy = static_cast<int>(ypos);
        EventQueue::getInstance()->post(std::make_shared<MouseEvent>(shared_from_this(), glm::ivec2 { ix, iy }, -1, MouseAction::None));
    });
    window->setMouseButtonCallback([&](int button, int action, int mods) -> void {
        glm::ivec2 pos = window->getCursorPosition();
        if (action == ag::Window::k_eventMouseActionPress) {
            EventQueue::getInstance()->post(std::make_shared<MouseEvent>(shared_from_this(), pos, button, MouseAction::Press));
        } else {
            EventQueue::getInstance()->post(std::make_shared<MouseEvent>(shared_from_this(), pos, button, MouseAction::Release));
        }
    });
    setBounds(Rect { { 0, 0 }, window->getSize() });
    setLayoutManager(std::make_shared<BorderLayout>());
}
}