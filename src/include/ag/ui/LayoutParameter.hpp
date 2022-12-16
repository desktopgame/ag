#pragma once
#include <memory>

namespace agui {
class LayoutParameter {
public:
    using Instance = std::shared_ptr<LayoutParameter>;
    explicit LayoutParameter() = default;
    virtual ~LayoutParameter() = default;

    static Instance empty();

private:
};
}