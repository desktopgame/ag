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
    , m_caretPosition(0)
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
    // draw caret
    glm::ivec2 caretOffset = bounds.position + glm::ivec2 { k_edgeThickness, k_edgeThickness };
    if (m_caretPosition > 0) {
        glm::ivec2 textSize = r->measureString(f.size, m_text.substr(0, m_caretPosition));
        textSize.y = 0;
        caretOffset += textSize;
    }
    if (m_blinkOnWait < k_blinkOnLength) {
        if (m_focusOn) {
            r->fillRect(caretOffset, glm::ivec2 { 2, bounds.size.y - k_edgeThickness * 2 }, glm::vec4 { 1, 1, 1, 1 });
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
void TextField::processKeyEvent(const std::shared_ptr<KeyEvent>& e)
{
    if (e->action == KeyAction::Type && m_focusOn) {
        m_text.push_back(e->keyChar);
        m_caretPosition++;
    }
}
}