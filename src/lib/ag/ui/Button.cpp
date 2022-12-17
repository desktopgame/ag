#include <ag/ui/Button.hpp>
#include <ag/ui/RenderingUtil.hpp>

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
    RenderingUtil util { r };
    const glm::vec4 buttonBack = { 0.1f, 0.1f, 0.1f, 1.f };
    const glm::vec4 buttonEdge = { 0.f, 0.f, 0.f, 1.f };
    util.fillBorderedRect(getBounds(), k_edgeThickness, buttonBack, buttonEdge);
    m_label->setFont(getFont());
    m_label->setBounds(getBounds());
    m_label->update(r);
}
}