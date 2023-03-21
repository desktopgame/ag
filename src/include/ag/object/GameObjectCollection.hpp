#pragma once
#include <ag/graphics/Renderer.hpp>
#include <ag/input/InputState.hpp>
#include <ag/object/GameObject.hpp>
#include <string>
#include <vector>

namespace ag {
class GameObjectCollection {
public:
    explicit GameObjectCollection();

    GameObject::Instance create(const std::string& name);
    void update(const ag::InputState& input, float deltaTime);
    void draw(const ag::Renderer::Instance& renderer);

    GameObject::Instance findByName(const std::string& name) const;
    GameObject::Instance findByTag(const std::string& tag) const;
    size_t size() const;

private:
    std::vector<GameObject::Instance> m_objects;
};
}