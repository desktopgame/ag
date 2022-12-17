#pragma once
#include <ag/ui/BorderLayoutParameter.hpp>
#include <ag/ui/LayoutManagerBase.hpp>

namespace agui {
class BorderLayout : public LayoutManagerBase {
public:
    explicit BorderLayout() = default;
    void layoutContainer(const std::shared_ptr<Container>& c) override;

    glm::ivec2 minimumLayoutSize(const std::shared_ptr<Container>& c) const override;
    glm::ivec2 preferredLayoutSize(const std::shared_ptr<Container>& c) const override;
    glm::ivec2 maximumLayoutSize(const std::shared_ptr<Container>& c) const override;

private:
    Component::Instance lookup(BorderPosition position) const;
};
}