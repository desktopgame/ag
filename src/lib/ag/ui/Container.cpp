#include <ag/ui/Container.hpp>
#include <ag/ui/ILayoutManager.hpp>
#include <ag/ui/Rect.hpp>
#include <algorithm>

namespace agui {
Container::Container()
    : Component()
    , m_components()
    , m_layoutManager()
{
}

void Container::profile()
{
    for (int i = 0; i < getComponentCount(); i++) {
        auto c = getComponent(i);
        c->profile();
    }
    if (m_layoutManager) {
        auto self = std::static_pointer_cast<Container>(shared_from_this());
        setMinimumSize(m_layoutManager->minimumLayoutSize(self));
        setPreferredSize(m_layoutManager->preferredLayoutSize(self));
        setMaximumSize(m_layoutManager->maximumLayoutSize(self));
    }
}

void Container::update(const std::shared_ptr<ag::Renderer>& r)
{
    if (isOpaque()) {
        r->fillRect(getLocation(), getSize(), getBackground());
    }
    for (auto c : m_components) {
        c->update(r);
    }
}

void Container::addComponent(const Component::Instance& component, const std::shared_ptr<LayoutParameter>& param)
{
    m_components.push_back(component);
    component->setParent(std::static_pointer_cast<Container>(shared_from_this()));
    if (m_layoutManager) {
        m_layoutManager->addLayoutComponent(component, param);
    }
}
void Container::removeComponent(const Component::Instance& component)
{
    auto iter = std::remove_if(m_components.begin(), m_components.end(), [component](Component::Instance e) -> bool {
        return e == component;
    });
    m_components.erase(iter, m_components.end());
    if (m_layoutManager) {
        m_layoutManager->removeLayoutComponent(component);
    }
}
Component::Instance Container::getComponent(int i) const { return m_components.at(i); }
int Container::getComponentCount() const { return static_cast<int>(m_components.size()); }
std::vector<Component::Instance> Container::getComponents() const { return m_components; }

void Container::setLayoutManager(const std::shared_ptr<ILayoutManager>& layoutManager) { m_layoutManager = layoutManager; }
std::shared_ptr<ILayoutManager> Container::getLayoutManager() const { return m_layoutManager; }

void Container::doLayoutTree()
{
    doLayout();
    for (int i = 0; i < getComponentCount(); i++) {
        auto c = std::dynamic_pointer_cast<Container>(getComponent(i));
        if (c) {
            c->doLayoutTree();
        }
    }
    m_valid = true;
}
// protected
void Container::doLayout()
{
    for (int i = 0; i < getComponentCount(); i++) {
        auto c = getComponent(i);
        c->profile();
    }
    if (m_layoutManager) {
        m_layoutManager->layoutContainer(std::static_pointer_cast<Container>(shared_from_this()));
    }
}
}