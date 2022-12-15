#pragma once
#include <ag/ui/Component.hpp>
#include <memory>
#include <vector>

namespace agui {
class ILayoutManager;
class LayoutParameter;
class Container : public Component {
public:
    explicit Container();
    virtual ~Container() = default;

    void addComponent(const Component::Instance& component, const std::shared_ptr<LayoutParameter>& param);
    Component::Instance getComponent(int i) const;
    int getComponentCount() const;
    std::vector<Component::Instance> getComponents() const;

    virtual void doLayout(const Rect& bounds) = 0;

private:
    std::vector<Component::Instance> m_components;
};
}