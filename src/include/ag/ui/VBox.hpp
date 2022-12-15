#pragma once
#include <ag/ui/Container.hpp>
#include <vector>

namespace agui {
class VBox : public Container {
public:
    explicit VBox(const std::vector<int>& weight);

protected:
    void doLayout(const Rect& bounds) override;

private:
    std::vector<int> m_weight;
};
}