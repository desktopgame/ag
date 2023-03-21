#include <ag/object/GameObjectCollection.hpp>
#include <algorithm>

namespace ag {

GameObjectCollection::GameObjectCollection()
    : m_objects()
{
}

GameObject::Instance GameObjectCollection::create(const std::string& name)
{
    auto obj = GameObject::create(name);
    m_objects.emplace_back(obj);
    return obj;
}
void GameObjectCollection::update(const ag::InputState& input, float deltaTime)
{
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

size_t GameObjectCollection::size() const { return m_objects.size(); }
}