#include "Debri.hpp"

Debri::Debri(const ag::GameObject::Instance& gameObject)
    : ag::Component(gameObject)
    , m_model()
{
}
void Debri::update(const ag::InputState& input, float deltaTime) { }
void Debri::draw(const ag::Renderer::Instance& renderer)
{
    if (m_model) {
        renderer->pushMatrix();
        renderer->translate(getGameObject()->getPosition());
        renderer->rotateY(glm::radians(20.0f));
        renderer->scale(glm::vec3(0.01f, 0.01f, 0.01f));
        renderer->translate(-getGameObject()->getPosition());
        renderer->drawModel(glm::vec3(0, 0, 0), m_model, ag::MeshDrawMode::ColorNoLight);
        renderer->popMatrix();
    }
}
void Debri::setModel(const ag::Model::Instance& model) { m_model = model; }
ag::Model::Instance Debri::getModel() const { return m_model; }
