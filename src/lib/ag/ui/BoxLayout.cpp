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
    int total = 0;
    for (int i = 0; i < getElementCount(); i++) {
        total += getParameter<BoxLayoutParameter>(i)->weight;
    }
    auto bounds = c->getBounds();
    int cc = c->getComponentCount();
    if (m_orientation == Orientation::Horizontal) {
        if (total == 0) {
            int w = bounds.size.x / cc;
            int h = bounds.size.y;
            int offs = 0;
            for (int i = 0; i < cc; i++) {
                auto comp = getComponent(i);
                comp->setSize({ w, h });
                comp->setLocation(bounds.position + glm::ivec2 { offs, 0 });
                offs += w;
            }
        } else {
            if (getElementCount() != c->getComponentCount()) {
                throw std::runtime_error("invalid component count.");
            }
            int h = bounds.size.y;
            int offs = 0;
            for (int i = 0; i < cc; i++) {
                float scale = (float)getParameter<BoxLayoutParameter>(i)->weight / (float)total;
                int w = static_cast<int>((float)bounds.size.x * scale);
                auto comp = getComponent(i);
                comp->setSize({ w, h });
                comp->setLocation(bounds.position + glm::ivec2 { offs, 0 });
                offs += w;
            }
        }
    } else {
        if (total == 0) {
            int w = bounds.size.x;
            int h = bounds.size.y / cc;
            int offs = 0;
            for (int i = 0; i < cc; i++) {
                auto comp = getComponent(i);
                comp->setSize({ w, h });
                comp->setLocation(bounds.position + glm::ivec2 { 0, offs });
                offs += h;
            }
        } else {
            if (getElementCount() != c->getComponentCount()) {
                throw std::runtime_error("invalid component count.");
            }
            int w = bounds.size.x;
            int offs = 0;
            for (int i = 0; i < cc; i++) {
                float scale = (float)getParameter<BoxLayoutParameter>(i)->weight / (float)total;
                int h = static_cast<int>((float)bounds.size.y * scale);
                auto comp = getComponent(i);
                comp->setSize({ w, h });
                comp->setLocation(bounds.position + glm::ivec2 { 0, offs });
                offs += h;
            }
        }
    }
}
}