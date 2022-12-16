#pragma once
#include <ag/ui/LayoutParameter.hpp>

namespace agui {
class BoxLayoutParameter : public LayoutParameter {
public:
    explicit BoxLayoutParameter(int weight);
    const int weight;

private:
};
}