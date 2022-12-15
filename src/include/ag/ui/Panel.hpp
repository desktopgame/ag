#pragma once
#include <ag/ui/Container.hpp>

namespace agui {
class Panel : public Container {
public:
    explicit Panel(const glm::vec4& color);
    virtual ~Panel() = default;

protected:
    void doLayout(const Rect& bounds) override;
};
}