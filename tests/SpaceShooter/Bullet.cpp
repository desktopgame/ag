#include "Bullet.hpp"
#include <ag/object/GameObject.hpp>

Bullet::Bullet(const std::shared_ptr<ag::GameObject>& gameObject)
    : ag::Component(gameObject)
    , m_direction()
    , m_speed()
    , m_lifetime(3.0f)
{
}

void Bullet::update(const ag::InputState& input, float deltaTime)
{
    auto obj = getGameObject();
    obj->setPosition(obj->getPosition() + (m_direction * m_speed * deltaTime));
    m_lifetime -= deltaTime;
    if (m_lifetime < 0.0f) {
        getGameObject()->destroy();
    }
}
void Bullet::draw(const ag::Renderer::Instance& renderer) { }

void Bullet::setDirection(const glm::vec3& direction) { m_direction = direction; }
glm::vec3 Bullet::getDirection() const { return m_direction; }

void Bullet::setSpeed(float speed) { m_speed = speed; }
float Bullet::getSpeed() const { return m_speed; }