#pragma once
#include <ag/graphics/Renderer.hpp>
#include <ag/input/InputState.hpp>
#include <memory>

namespace ag {
class GameObject;
class Component : public std::enable_shared_from_this<Component> {
public:
    using Instance = std::shared_ptr<Component>;
    explicit Component(const std::shared_ptr<GameObject>& gameObject);
    virtual ~Component() = default;
    virtual void start();
    virtual void update(const InputState& input, float deltaTime) = 0;
    virtual void draw(const Renderer::Instance& renderer) = 0;
    virtual void onDestroy();

    std::shared_ptr<GameObject> getGameObject() const;

private:
    std::weak_ptr<GameObject> m_gameObject;
};
}