#pragma once
#include <ag/native/glm.hpp>
#include <memory>

namespace agui {
class Component;
class Container;
class LayoutParameter;
class ILayoutManager {
public:
    explicit ILayoutManager() = default;
    virtual ~ILayoutManager() = default;

    virtual void addLayoutComponent(const std::shared_ptr<Component>& c, const std::shared_ptr<LayoutParameter>& param) = 0;
    virtual void removeLayoutComponent(const std::shared_ptr<Component>& c) = 0;
    virtual void layoutContainer(const std::shared_ptr<Container>& c) = 0;

    // virtual glm::ivec2 minimumLayoutSize(const std::shared_ptr<Container>& c) const = 0;
    // virtual glm::ivec2 preferredLayoutSize(const std::shared_ptr<Container>& c) const = 0;
    // virtual glm::ivec2 maximumLayoutSize(const std::shared_ptr<Container>& c) const = 0;

private:
};
}