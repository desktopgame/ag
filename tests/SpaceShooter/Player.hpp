#pragma once
#include <ag/graphics/Model.hpp>
#include <ag/object/Component.hpp>
#include <ag/object/GameObjectCollection.hpp>

class Player : public ag::Component {
public:
    explicit Player(const std::shared_ptr<ag::GameObject>& gameObject);

    void setup(ag::GameObjectCollection& gameObjectCollection, const ag::Model::Instance& bulletModel);
    void update(const ag::InputState& input, float deltaTime) override;
    void draw(const ag::Renderer::Instance& renderer) override;

private:
    void createBullet();
    ag::GameObjectCollection* m_gameObjectCollection;
    ag::Model::Instance m_bulletModel;
};