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

    void profile() override;
    void update(const std::shared_ptr<ag::Renderer>& r) override;

    void addComponent(const Component::Instance& component, const std::shared_ptr<LayoutParameter>& param);
    Component::Instance getComponent(int i) const;
    int getComponentCount() const;
    std::vector<Component::Instance> getComponents() const;

    void setLayoutManager(const std::shared_ptr<ILayoutManager>& layoutManager);
    std::shared_ptr<ILayoutManager> getLayoutManager() const;

    void doLayoutTree();

protected:
    virtual void doLayout();

private:
    std::vector<Component::Instance> m_components;
    std::shared_ptr<ILayoutManager> m_layoutManager;
};
}