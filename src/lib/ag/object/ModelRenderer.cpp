#include <ag/object/ModelRenderer.hpp>

namespace ag {
ModelRenderer::ModelRenderer(const GameObject::Instance& gameObject)
    : Component(gameObject)
    , m_model()
{
}
void ModelRenderer::update(const InputState& input, float deltaTime) { }
void ModelRenderer::draw(const Renderer::Instance& renderer)
{
    auto obj = getGameObject();
    auto position = obj->getPosition();
    auto rotation = obj->getRotation();
    auto scale = obj->getScale();
    if (m_model) {
        renderer->pushMatrix();
        renderer->translate(position);
        renderer->rotateX(glm::radians(rotation.x));
        renderer->rotateY(glm::radians(rotation.y));
        renderer->rotateZ(glm::radians(rotation.z));
        renderer->scale(scale);
        renderer->translate(-position);
        renderer->drawModel(glm::vec3(0, 0, 0), m_model, MeshDrawMode::ColorNoLight);
        renderer->popMatrix();
    }
}
void ModelRenderer::setModel(const Model::Instance& model) { m_model = model; }
Model::Instance ModelRenderer::getModel() const { return m_model; }
}