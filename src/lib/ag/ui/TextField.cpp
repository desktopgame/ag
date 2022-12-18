#include <ag/ui/MouseEvent.hpp>
#include <ag/ui/RenderingUtil.hpp>
#include <ag/ui/TextField.hpp>

namespace agui {
TextField::TextField()
    : Component()
    , m_focusOn(false)
    , m_text(u"")
    , m_blinkOnWait()
    , m_blinkOffWait(k_blinkOffLength)
{
    setEventMask(DeviceEventType::MouseEvent | DeviceEventType::KeyEvent);
    setPreferredSize({ 200, 20 });
}

void TextField::profile()
{
}
void TextField::update(const std::shared_ptr<ag::Renderer>& r)
{
    auto f = getFont();
    auto bounds = getBounds();
    RenderingUtil util { r };
    const glm::vec4 buttonBack = m_focusOn ? glm::vec4 { 0.3f, 0.3f, 0.3f, 1.f } : glm::vec4 { 0.2f, 0.2f, 0.2f, 1.f };
    const glm::vec4 buttonEdge = { 0.f, 0.f, 0.f, 1.f };
    util.fillBorderedRect(bounds, k_edgeThickness, buttonBack, buttonEdge);
    r->setFontMap(f.map);
    r->drawString(bounds.position + glm::ivec2 { k_edgeThickness, k_edgeThickness }, f.size, m_text, getForeground());
    if (m_blinkOnWait < k_blinkOnLength) {
        if (m_focusOn) {
            r->fillRect(bounds.position + glm::ivec2 { k_edgeThickness, k_edgeThickness }, glm::ivec2 { 2, bounds.size.y - k_edgeThickness * 2 }, glm::vec4 { 1, 1, 1, 1 });
        }
        m_blinkOnWait++;
    } else {
        if (m_blinkOffWait-- == 0) {
            m_blinkOffWait = k_blinkOffLength;
            m_blinkOnWait = 0;
        }
    }
}
// protected
void TextField::processMouseEvent(const std::shared_ptr<MouseEvent>& e)
{
    if (e->action == MouseAction::Press) {
        m_focusOn = getBounds().contains(e->position);
    }
}
}