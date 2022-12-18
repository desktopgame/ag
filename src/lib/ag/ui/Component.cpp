#include <ag/ui/Component.hpp>
#include <ag/ui/Container.hpp>
#include <cassert>

namespace agui {
Component::Component()
    : m_location()
    , m_size()
    , m_minimumSize()
    , m_preferredSize()
    , m_maximumSize()
    , m_foreground(1.f, 1.f, 1.f, 1.f)
    , m_background(0.2f, 0.2f, 0.2f, 1.f)
    , m_font(Font { nullptr, 12 })
    , m_parent()
    , m_opaque(false)
    , m_eventMask(0)
    , m_valid(false)
{
}

void Component::setLocation(const glm::ivec2& location)
{
    assert(location.x >= 0);
    assert(location.y >= 0);
    m_location = location;
    invalidate();
}
glm::ivec2 Component::getLocation() const { return m_location; }

void Component::setSize(const glm::ivec2& size)
{
    assert(size.x > 0);
    assert(size.y > 0);
    m_size = size;
    invalidate();
}
glm::ivec2 Component::getSize() const { return m_size; }

void Component::setBounds(const Rect& bounds)
{
    setLocation(bounds.position);
    setSize(bounds.size);
}
Rect Component::getBounds() const { return Rect { m_location, m_size }; }

void Component::setMinimumSize(const glm::ivec2& minimumSize) { m_minimumSize = minimumSize; }
glm::ivec2 Component::getMinimumSize() const { return m_minimumSize; }

void Component::setPreferredSize(const glm::ivec2& preferredSize) { m_preferredSize = preferredSize; }
glm::ivec2 Component::getPreferredSize() const { return m_preferredSize; }

void Component::setMaximumSize(const glm::ivec2& maximumSize) { m_maximumSize = maximumSize; }
glm::ivec2 Component::getMaximumSize() const { return m_maximumSize; }

void Component::setForeground(const glm::vec4& foreground) { m_foreground = foreground; }
glm::vec4 Component::getForeground() const { return m_foreground; }

void Component::setBackground(const glm::vec4& background) { m_background = background; }
glm::vec4 Component::getBackground() const { return m_background; }

void Component::setFont(const Font& font) { m_font = font; }
Font Component::getFont() const
{
    if (!m_font.map) {
        auto pp = getParent().lock();
        if (pp) {
            return pp->getFont();
        }
    }
    return m_font;
}

void Component::setParent(const std::weak_ptr<Container>& parent) { m_parent = parent; }
std::weak_ptr<Container> Component::getParent() const { return m_parent; }

void Component::setOpaque(bool opaque) { m_opaque = opaque; }
bool Component::isOpaque() const { return m_opaque; }

void Component::invalidate()
{
    auto pp = getParent().lock();
    if (pp) {
        pp->invalidate();
    }
    m_valid = false;
}
void Component::validate()
{
    if (!m_valid) {
        auto self = std::dynamic_pointer_cast<Container>(shared_from_this());
        if (self) {
            self->doLayoutTree();
        }
        m_valid = true;
    }
}
void Component::revalidate()
{
    invalidate();
    std::shared_ptr<Container> pp = getParent().lock();
    while (pp) {
        auto next = pp->getParent().lock();
        if (next) {
            pp = next;
        } else
            break;
    }
    if (pp) {
        pp->validate();
    }
}

void Component::dispatchEvent(const std::shared_ptr<DeviceEvent>& e)
{
    if (e->isConsumed()) {
        return;
    }
    if (e->type == DeviceEventType::MouseEvent && (getEventMask() & DeviceEventType::MouseEvent) > 0) {
        processMouseEvent(std::static_pointer_cast<MouseEvent>(e));
    }
    if (e->type == DeviceEventType::KeyEvent && (getEventMask() & DeviceEventType::KeyEvent) > 0) {
        processKeyEvent(std::static_pointer_cast<KeyEvent>(e));
    }
}

// protected
void Component::setEventMask(int eventMask) { m_eventMask = eventMask; }
int Component::getEventMask() const { return m_eventMask; }
void Component::processMouseEvent(const std::shared_ptr<MouseEvent>& e)
{
}
void Component::processKeyEvent(const std::shared_ptr<KeyEvent>& e)
{
}
}