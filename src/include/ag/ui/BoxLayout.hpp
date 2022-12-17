#pragma once
#include <ag/ui/LayoutManagerBase.hpp>
#include <ag/ui/Orientation.hpp>

namespace agui {
class BoxLayout : public LayoutManagerBase {
public:
    explicit BoxLayout(Orientation orientation);
    void layoutContainer(const std::shared_ptr<Container>& c) override;

    glm::ivec2 minimumLayoutSize(const std::shared_ptr<Container>& c) const override;
    glm::ivec2 preferredLayoutSize(const std::shared_ptr<Container>& c) const override;
    glm::ivec2 maximumLayoutSize(const std::shared_ptr<Container>& c) const override;

private:
    glm::ivec2 maxPreferredLayoutSize() const;
    Orientation m_orientation;
};
}