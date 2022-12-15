#include <ag/ui/Panel.hpp>

namespace agui {
Panel::Panel(const glm::vec4& color)
    : Container()
{
    setBackground(color);
}
void Panel::doLayout(const Rect& bounds)
{
}
}