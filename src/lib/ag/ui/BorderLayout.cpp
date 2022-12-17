#include <ag/ui/BorderLayout.hpp>
#include <ag/ui/Container.hpp>
#include <algorithm>

namespace agui {
void BorderLayout::layoutContainer(const std::shared_ptr<Container>& c)
{
    auto bounds = c->getBounds();
    auto top = lookup(BorderPosition::Top);
    auto left = lookup(BorderPosition::Left);
    auto center = lookup(BorderPosition::Center);
    auto right = lookup(BorderPosition::Right);
    auto bottom = lookup(BorderPosition::Bottom);
    int toffs = 0;
    int boffs = bounds.bottom();
    int loffs = bounds.left();
    int roffs = bounds.right();
    if (top) {
        auto tPref = top->getPreferredSize();
        top->setLocation(bounds.position);
        top->setSize({ bounds.size.x, tPref.y });
        toffs += tPref.y;
    }
    if (bottom) {
        auto bPref = bottom->getPreferredSize();
        bottom->setLocation(glm::ivec2 { bounds.position.x, bounds.bottom() - bPref.y });
        bottom->setSize({ bounds.size.x, bPref.y });
        boffs -= bPref.y;
    }
    if (left) {
        auto lPref = left->getPreferredSize();
        left->setLocation({ bounds.left(), toffs });
        left->setSize({ lPref.x, boffs - toffs });
        loffs += lPref.x;
    }
    if (right) {
        auto rPref = right->getPreferredSize();
        right->setLocation({ bounds.right() - rPref.x, toffs });
        right->setSize({ rPref.x, boffs - toffs });
        roffs -= rPref.x;
    }
    if (center) {
        center->setLocation({ loffs, toffs });
        center->setSize({ std::max(roffs - loffs, 1), boffs - toffs });
    }
}
glm::ivec2 BorderLayout::minimumLayoutSize(const std::shared_ptr<Container>& c) const { return preferredLayoutSize(c); }
glm::ivec2 BorderLayout::preferredLayoutSize(const std::shared_ptr<Container>& c) const
{
    int width = 0;
    int height = 0;
    auto top = lookup(BorderPosition::Top);
    auto left = lookup(BorderPosition::Left);
    auto center = lookup(BorderPosition::Center);
    auto right = lookup(BorderPosition::Right);
    auto bottom = lookup(BorderPosition::Bottom);
    if (top) {
        auto tPref = top->getPreferredSize();
        height += tPref.y;
        width = std::max(0, tPref.x);
    }
    if (bottom) {
        auto bPref = bottom->getPreferredSize();
        height += bPref.y;
        width = std::max(0, bPref.x);
    }
    if (center || left || right) {
        auto cPref = center ? center->getPreferredSize() : glm::ivec2 { 0, 0 };
        auto lPref = left ? left->getPreferredSize() : glm::ivec2 { 0, 0 };
        auto rPref = right ? right->getPreferredSize() : glm::ivec2 { 0, 0 };
        height += std::max(cPref.y, std::max(lPref.y, rPref.y));
        width = std::max(width, cPref.x + lPref.x + rPref.x);
    }
    return { width, height };
}
glm::ivec2 BorderLayout::maximumLayoutSize(const std::shared_ptr<Container>& c) const { return preferredLayoutSize(c); }
// private
Component::Instance BorderLayout::lookup(BorderPosition position) const
{
    for (int i = 0; i < getElementCount(); i++) {
        if (getParameter<BorderLayoutParameter>(i)->position == position) {
            return getComponent(i);
        }
    }
    return nullptr;
}
}
