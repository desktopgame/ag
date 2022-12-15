#include <ag/ui/VBox.hpp>
#include <stdexcept>

namespace agui {
VBox::VBox(const std::vector<int>& weight)
    : m_weight(weight)
{
}
void VBox::doLayout(const Rect& bounds)
{
    int cc = getComponentCount();
    if (m_weight.size() == 0) {
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
        if (m_weight.size() != getComponentCount()) {
            throw std::runtime_error("invalid component count.");
        }
        int total = 0;
        for (int w : m_weight) {
            total += w;
        }
        int w = bounds.size.x;
        int offs = 0;
        for (int i = 0; i < cc; i++) {
            float scale = (float)m_weight.at(i) / (float)total;
            int h = static_cast<int>((float)bounds.size.y * scale);
            auto comp = getComponent(i);
            comp->setSize({ w, h });
            comp->setLocation(bounds.position + glm::ivec2 { 0, offs });
            offs += h;
        }
    }
}
}