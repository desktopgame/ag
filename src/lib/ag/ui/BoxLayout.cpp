#include <ag/ui/BoxLayout.hpp>
#include <ag/ui/BoxLayoutParameter.hpp>
#include <ag/ui/Container.hpp>

namespace agui {

BoxLayout::BoxLayout(Orientation orientation)
    : m_orientation(orientation)
{
}
void BoxLayout::layoutContainer(const std::shared_ptr<Container>& c)
{
    auto bounds = c->getBounds();
    auto mp = c->getSize();
    if (m_orientation == Orientation::Horizontal) {
        auto offset = bounds.position;
        for (int i = 0; i < c->getComponentCount(); i++) {
            auto child = c->getComponent(i);
            auto pref = child->getPreferredSize();
            child->setLocation(offset);
            child->setSize({ pref.x, mp.y });
            offset.x += pref.x;
        }
    } else {
        auto offset = bounds.position;
        for (int i = 0; i < c->getComponentCount(); i++) {
            auto child = c->getComponent(i);
            auto pref = child->getPreferredSize();
            child->setLocation(offset);
            child->setSize({ mp.x, pref.y });
            offset.y += pref.y;
        }
    }
}

glm::ivec2 BoxLayout::minimumLayoutSize(const std::shared_ptr<Container>& c) const { return preferredLayoutSize(c); }
glm::ivec2 BoxLayout::preferredLayoutSize(const std::shared_ptr<Container>& c) const
{
    auto mp = maxPreferredLayoutSize();
    int width = 0;
    int height = 0;
    if (m_orientation == Orientation::Horizontal) {
        for (int i = 0; i < c->getComponentCount(); i++) {
            auto child = c->getComponent(i);
            auto pref = child->getPreferredSize();
            width += pref.x;
        }
        height = mp.y;
    } else {
        for (int i = 0; i < c->getComponentCount(); i++) {
            auto child = c->getComponent(i);
            auto pref = child->getPreferredSize();
            height += pref.y;
        }
        width = mp.x;
    }
    return { width, height };
}
glm::ivec2 BoxLayout::maximumLayoutSize(const std::shared_ptr<Container>& c) const { return preferredLayoutSize(c); }
// private

glm::ivec2 BoxLayout::maxPreferredLayoutSize() const
{
    glm::ivec2 ret { -1, -1 };
    for (int i = 0; i < getElementCount(); i++) {
        auto c = getComponent(i);
        auto p = c->getPreferredSize();
        if (ret.x < p.x) {
            ret.x = p.x;
        }
        if (ret.y < p.y) {
            ret.y = p.y;
        }
    }
    return ret;
}
glm::ivec2 BoxLayout::sumPreferredLayoutSize() const
{
    glm::ivec2 ret { 0, 0 };
    for (int i = 0; i < getElementCount(); i++) {
        auto c = getComponent(i);
        auto p = c->getPreferredSize();
        ret.x += p.x;
        ret.y += p.y;
    }
    return ret;
}
}