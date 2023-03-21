#include <ag/object/GameObjectCollection.hpp>
#include <algorithm>

namespace ag {

GameObjectCollection::GameObjectCollection()
    : m_objects()
    , m_buffer()
{
}

GameObject::Instance GameObjectCollection::create(const std::string& name)
{
    auto obj = GameObject::create(name);
    m_buffer.emplace_back(obj);
    return obj;
}
void GameObjectCollection::update(const ag::InputState& input, float deltaTime)
{
    for (auto obj : m_buffer) {
        m_objects.emplace_back(obj);
    }
    m_buffer.clear();
    for (auto obj : m_objects) {
        if (obj->isDestroyed()) {
            continue;
        }
        obj->update(input, deltaTime);
    }
    auto iter = std::remove_if(m_objects.begin(), m_objects.end(), [](GameObject::Instance e) -> bool {
        return e->isDestroyed();
    });
    m_objects.erase(iter, m_objects.end());
}
void GameObjectCollection::draw(const ag::Renderer::Instance& renderer)
{
    for (auto obj : m_objects) {
        if (obj->isDestroyed()) {
            continue;
        }
        obj->draw(renderer);
    }
}

GameObject::Instance GameObjectCollection::findByName(const std::string& name) const
{
    for (auto e : m_objects) {
        if (e->getName() == name) {
            return e;
        }
    }
    return nullptr;
}
GameObject::Instance GameObjectCollection::findByTag(const std::string& tag) const
{
    for (auto e : m_objects) {
        if (e->getTag() == tag) {
            return e;
        }
    }
    return nullptr;
}
size_t GameObjectCollection::size() const { return m_objects.size(); }
}