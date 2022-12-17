#include <ag/ui/Button.hpp>

namespace agui {
Button::Button(const std::u16string& text)
    : Component()
    , m_label(std::make_shared<Label>(text))
{
}

void Button::update(const std::shared_ptr<ag::Renderer>& r)
{
    auto b = getBounds();
    const int thi = 3;
    r->fillRect(b.position, getSize(), getBackground());
    r->fillRect(b.position, { thi, b.size.y }, { 0, 0, 1, 1 });
    r->fillRect(b.position, { b.size.x, thi }, { 0, 0, 1, 1 });
    r->fillRect({ b.right() - thi, b.top() }, { thi, b.size.y }, { 0, 0, 1, 1 });
    r->fillRect({ b.left(), b.bottom() - thi }, { b.size.x, thi }, { 0, 0, 1, 1 });
    m_label->setFont(getFont());
    m_label->setBounds(getBounds());
    m_label->update(r);
}
}