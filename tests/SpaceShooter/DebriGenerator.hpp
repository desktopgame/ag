#pragma once
#include "Player.hpp"
#include <ag/graphics/Model.hpp>
#include <ag/object/Component.hpp>
#include <ag/object/GameObject.hpp>
#include <ag/object/GameObjectCollection.hpp>
#include <vector>

class DebriGenerator : public ag::Component {
public:
    explicit DebriGenerator(const std::shared_ptr<ag::GameObject>& gameObject);

    void setup(ag::GameObjectCollection& gameObjectCollection, const std::shared_ptr<Player> player, const ag::Model::Instance& debriModel);
    void update(const ag::InputState& input, float deltaTime) override;
    void draw(const ag::Renderer::Instance& renderer) override;

private:
    void createDebri();
    ag::GameObjectCollection* m_gameObjectCollection;
    std::shared_ptr<Player> m_player;
    ag::Model::Instance m_debriModel;
    std::vector<ag::GameObject::Instance> m_debriList;
};