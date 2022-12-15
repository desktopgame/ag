#include <ag/ui/HBox.hpp>
#include <stdexcept>

namespace agui {
HBox::HBox(const std::vector<int>& weight)
    : m_weight(weight)
{
}
void HBox::doLayout(const Rect& bounds)
{
    int cc = getComponentCount();
    if (m_weight.size() == 0) {
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
        if (m_weight.size() != getComponentCount()) {
            throw std::runtime_error("invalid component count.");
        }
        int total = 0;
        for (int w : m_weight) {
            total += w;
        }
        int h = bounds.size.y;
        int offs = 0;
        for (int i = 0; i < cc; i++) {
            float scale = (float)m_weight.at(i) / (float)total;
            int w = static_cast<int>((float)bounds.size.x * scale);
            auto comp = getComponent(i);
            comp->setSize({ w, h });
            comp->setLocation(bounds.position + glm::ivec2 { offs, 0 });
            offs += w;
        }
    }
}
}