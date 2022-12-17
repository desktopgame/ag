#pragma once
#include <ag/ui/LayoutParameter.hpp>

namespace agui {
enum BorderPosition {
    Top,
    Left,
    Center,
    Right,
    Bottom
};
class BorderLayoutParameter : public LayoutParameter {
public:
    BorderLayoutParameter(BorderPosition position);
    const BorderPosition position;
};
}