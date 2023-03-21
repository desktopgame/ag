#pragma once
#include <ag/object/Component.hpp>

class Bullet : public ag::Component {
public:
    explicit Bullet(const std::shared_ptr<ag::GameObject>& gameObject);

    void update(const ag::InputState& input, float deltaTime) override;
    void draw(const ag::Renderer::Instance& renderer) override;

    void setDirection(const glm::vec3& direction);
    glm::vec3 getDirection() const;

    void setSpeed(float speed);
    float getSpeed() const;

private:
    glm::vec3 m_direction;
    float m_speed;
    float m_lifetime;
};