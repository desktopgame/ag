#include <ag/ui/Button.hpp>

namespace agui {
Button::Button(const std::u16string& text)
    : Component()
    , m_label(std::make_shared<Label>(text))
{
}

void Button::profile()
{
    const int add = k_additionalSize;
    m_label->setFont(getFont());
    m_label->profile();
    setPreferredSize(m_label->getPreferredSize() + glm::ivec2 { add, add });
}
void Button::update(const std::shared_ptr<ag::Renderer>& r)
{
    auto b = getBounds();
    const int t_ = k_edgeThickness;
    const glm::vec4 buttonBack = { 0.1f, 0.1f, 0.1f, 1.f };
    const glm::vec4 buttonEdge = { 0.f, 0.f, 0.f, 1.f };
    r->fillRect(b.position, getSize(), buttonBack);
    r->fillRect(b.position, { t_, b.size.y }, buttonEdge);
    r->fillRect(b.position, { b.size.x, t_ }, buttonEdge);
    r->fillRect({ b.right() - t_, b.top() }, { t_, b.size.y }, buttonEdge);
    r->fillRect({ b.left(), b.bottom() - t_ }, { b.size.x, t_ }, buttonEdge);
    m_label->setFont(getFont());
    m_label->setBounds(getBounds());
    m_label->update(r);
}
}