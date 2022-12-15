#include <ag/ui/Container.hpp>

namespace agui {
Container::Container()
    : Component()
    , m_components()
{
}

void Container::update(const std::shared_ptr<ag::Renderer>& r)
{
    r->fillRect(getLocation(), getSize(), getBackground());
    for (auto c : m_components) {
        c->update(r);
    }
}

void Container::addComponent(const Component::Instance& component)
{
    m_components.push_back(component);
}
Component::Instance Container::getComponent(int i) const { return m_components.at(i); }
int Container::getComponentCount() const { return static_cast<int>(m_components.size()); }
std::vector<Component::Instance> Container::getComponents() const { return m_components; }

}