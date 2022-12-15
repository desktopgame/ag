#include <ag/ui/Button.hpp>

namespace agui {
Button::Button(const std::u16string& text)
    : Component()
    , m_label(std::make_shared<Label>(text))
{
}

void Button::update(const std::shared_ptr<ag::Renderer>& r)
{
    r->fillRect(getLocation(), getSize(), getBackground());
    m_label->setBounds(getBounds());
    m_label->update(r);
}
}