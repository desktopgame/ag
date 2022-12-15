#include <ag/ui/Label.hpp>

namespace agui {
Label::Label(const std::u16string& text)
    : m_text(text)
{
}
void Label::update(const std::shared_ptr<ag::Renderer>& r)
{
    r->drawString(getLocation(), 20, m_text, getForeground());
}
}