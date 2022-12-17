#include <ag/ui/Component.hpp>
#include <ag/ui/Container.hpp>

namespace agui {
Component::Component()
    : m_location()
    , m_size()
    , m_minimumSize()
    , m_preferredSize()
    , m_maximumSize()
    , m_foreground(1.f, 1.f, 1.f, 1.f)
    , m_background(0.6f, 0.6f, 0.6f, 1.f)
    , m_font(Font { nullptr, 12 })
    , m_parent()
{
}

void Component::setLocation(const glm::ivec2& location) { m_location = location; }
glm::ivec2 Component::getLocation() const { return m_location; }

void Component::setSize(const glm::ivec2& size) { m_size = size; }
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

}