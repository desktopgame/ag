#include <ag/ui/Button.hpp>
#include <ag/ui/MouseEvent.hpp>
#include <ag/ui/RenderingUtil.hpp>

namespace agui {
Button::Button(const std::u16string& text)
    : Component()
    , m_label(std::make_shared<Label>(text))
    , m_press(false)
{
    setEventMask(DeviceEventType::MouseEvent);
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
    const glm::vec4 buttonBack = m_press ? glm::vec4 { 0.2f, 0.2f, 0.2f, 1.f } : glm::vec4 { 0.1f, 0.1f, 0.1f, 1.f };
    const glm::vec4 buttonEdge = { 0.f, 0.f, 0.f, 1.f };
    util.fillBorderedRect(getBounds(), k_edgeThickness, buttonBack, buttonEdge);
    m_label->setFont(getFont());
    m_label->setBounds(getBounds());
    m_label->update(r);
}
// protected
void Button::processMouseEvent(const std::shared_ptr<MouseEvent>& e)
{
    if (getBounds().contains(e->position) && (e->action == MouseAction::Press || e->action == MouseAction::Release)) {
        m_press = e->action == MouseAction::Press;
        e->consume();
    }
}
}