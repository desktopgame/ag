#pragma once
#include <ag/ui/Component.hpp>
#include <ag/ui/LayoutParameter.hpp>

namespace agui {
class LayoutElement {
public:
    explicit LayoutElement(const Component::Instance& component, const LayoutParameter::Instance& param);
    const Component::Instance component;
    const LayoutParameter::Instance param;

private:
};
}