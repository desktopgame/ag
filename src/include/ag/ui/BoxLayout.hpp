#pragma once
#include <ag/ui/LayoutManagerBase.hpp>
#include <ag/ui/Orientation.hpp>

namespace agui {
class BoxLayout : public LayoutManagerBase {
public:
    explicit BoxLayout(Orientation orientation);
    void layoutContainer(const std::shared_ptr<Container>& c) override;

private:
    Orientation m_orientation;
};
}