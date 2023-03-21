#pragma once
#include <ag/graphics/Model.hpp>
#include <ag/object/Component.hpp>
#include <ag/object/GameObject.hpp>

namespace ag {
class ModelRenderer : public Component {
public:
    explicit ModelRenderer(const GameObject::Instance& gameObject);
    void update(const InputState& input, float deltaTime) override;
    void draw(const Renderer::Instance& renderer) override;

    void setModel(const Model::Instance& model);
    Model::Instance getModel() const;

private:
    Model::Instance m_model;
};
}