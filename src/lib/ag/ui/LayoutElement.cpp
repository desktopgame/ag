#include <ag/ui/LayoutElement.hpp>

namespace agui {
LayoutElement::LayoutElement(const Component::Instance& component, const LayoutParameter::Instance& param)
    : component(component)
    , param(param)
{
}
}