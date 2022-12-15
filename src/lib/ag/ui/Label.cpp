#include <ag/ui/Label.hpp>

namespace agui {
Label::Label(const std::u16string& text)
    : m_text(text)
{
}
void Label::update(const std::shared_ptr<ag::Renderer>& r)
{
    auto b = getBounds();
    auto ms = r->measureString(20, m_text);
    if (b.size.x > ms.x) {
        b.position.x = b.position.x + (b.size.x - ms.x) / 2;
    }
    if (b.size.y > ms.y) {
        b.position.y = b.position.y + (b.size.y - ms.y) / 2;
    }
    r->drawString(b.position, 20, m_text, getForeground());
}
}