#pragma once
#include <ag/ui/Container.hpp>
#include <vector>

namespace agui {
class HBox : public Container {
public:
    explicit HBox(const std::vector<int>& weight);
    void doLayout(const Rect& bounds) override;

private:
    std::vector<int> m_weight;
};
}