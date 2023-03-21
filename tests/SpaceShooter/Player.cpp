#include "Player.hpp"
#include "Bullet.hpp"
#include <ag/object/ModelRenderer.hpp>

Player::Player(const std::shared_ptr<ag::GameObject>& gameObject)
    : ag::Component(gameObject)
    , m_gameObjectCollection(nullptr)
{
}

void Player::setup(ag::GameObjectCollection& gameObjectCollection, const ag::Model::Instance& bulletModel)
{
    m_gameObjectCollection = &gameObjectCollection;
    m_bulletModel = bulletModel;
}
void Player::update(const ag::InputState& input, float deltaTime)
{
    auto pos = getGameObject()->getPosition();
    float speed = 1.0f;
    if (input.getKeyboardState().getKeyState(ag::KeyCode::left) == ag::ButtonState::Held) {
        pos.x -= 10.0f * deltaTime;
    } else if (input.getKeyboardState().getKeyState(ag::KeyCode::right) == ag::ButtonState::Held) {
        pos.x += 10.0f * deltaTime;
    } else if (input.getKeyboardState().getKeyState(ag::KeyCode::up) == ag::ButtonState::Held) {
        speed = 3.0f;
    } else if (input.getKeyboardState().getKeyState(ag::KeyCode::z) == ag::ButtonState::Held) {
        createBullet();
    }
    pos.z -= speed * deltaTime;
    getGameObject()->setPosition(pos);
}
void Player::draw(const ag::Renderer::Instance& renderer) { }
// private
void Player::createBullet()
{
    ag::GameObject::Instance ret = m_gameObjectCollection->create("Bullet");
    auto debri = std::make_shared<ag::ModelRenderer>(ret);
    auto bullet = std::make_shared<Bullet>(ret);
    bullet->setDirection({ 0, 0, -1 });
    bullet->setSpeed(20);
    debri->setModel(m_bulletModel);
    ret->setPosition({ 0, 0, 10 });
    ret->setScale({ 0.01f, 0.01f, 0.01f });
    ret->addComponent(debri);
    ret->addComponent(bullet);
}