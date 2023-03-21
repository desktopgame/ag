#include "DebriGenerator.hpp"
#include <ag/object/ModelRenderer.hpp>
#include <ag/util/Random.hpp>
#include <algorithm>

DebriGenerator::DebriGenerator(const std::shared_ptr<ag::GameObject>& gameObject)
    : ag::Component(gameObject)
{
}
void DebriGenerator::setup(ag::GameObjectCollection& gameObjectCollection, const std::shared_ptr<Player> player, const ag::Model::Instance& debriModel)
{
    m_gameObjectCollection = &gameObjectCollection;
    m_player = player;
    m_debriModel = debriModel;
    for (int i = 0; i < 10; i++) {
        createDebri();
    }
}
void DebriGenerator::update(const ag::InputState& input, float deltaTime)
{
    for (auto debri : m_debriList) {
        if ((debri->getPosition().z - m_player->getGameObject()->getPosition().z) > 3.0f) {
            debri->destroy();
        }
    }
    size_t size = m_debriList.size();
    auto iter = std::remove_if(m_debriList.begin(), m_debriList.end(), [](ag::GameObject::Instance e) -> bool {
        return e->isDestroyed();
    });
    m_debriList.erase(iter, m_debriList.end());
    while (m_debriList.size() < size) {
        createDebri();
    }
}
void DebriGenerator::draw(const ag::Renderer::Instance& renderer) { }
// private
void DebriGenerator::createDebri()
{
    ag::GameObject::Instance ret = m_gameObjectCollection->create("Debri");
    float pz = m_player->getGameObject()->getPosition().z;
    auto debri = std::make_shared<ag::ModelRenderer>(ret);
    debri->setModel(m_debriModel);
    ret->setPosition({ ag::Random::range(-4, 4) * 3.0f, 0, pz - (ag::Random::range(4, 8) * 3.0f) });
    ret->setScale({ 0.01f, 0.01f, 0.01f });
    ret->addComponent(debri);
    m_debriList.emplace_back(ret);
}