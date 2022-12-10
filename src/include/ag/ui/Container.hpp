#pragma once
#include <ag/ui/Component.hpp>
#include <memory>
#include <vector>

namespace agui {
class ILayoutManager;
class LayoutParameter;
class Container : public Component {
public:
    explicit Container() = default;
    virtual ~Container() = default;

    void addComponent(const Component::Instance& component, const std::shared_ptr<LayoutParameter>& param);
    Component::Instance getComponent(int i) const;
    int getComponentCount() const;
    std::vector<Component::Instance> getComponents() const;

    void setLayoutManager(const std::shared_ptr<ILayoutManager>& layoutManager);
    std::shared_ptr<ILayoutManager> getLayoutManager() const;

private:
    std::vector<Component::Instance> m_components;
};
}