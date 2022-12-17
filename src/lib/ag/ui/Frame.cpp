#include <ag/ui/Frame.hpp>

namespace agui {
Frame::Frame(const ag::Window::Instance& window)
    : Container()
    , m_window(window)
{
    window->setWindowSizeCallback([&](int w, int h) -> void {
        setBounds(Rect { { 0, 0 }, { w, h } });
    });
    setBounds(Rect { { 0, 0 }, window->getSize() });
    setLayoutManager(std::make_shared<BorderLayout>());
}
}