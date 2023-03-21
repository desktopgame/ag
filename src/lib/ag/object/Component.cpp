#include <ag/object/Component.hpp>

namespace ag {

Component::Component(const std::shared_ptr<GameObject>& gameObject)
    : m_gameObject(gameObject)
{
}
void Component::onDestroy() { }
std::shared_ptr<GameObject> Component::getGameObject() const { return m_gameObject; }
}