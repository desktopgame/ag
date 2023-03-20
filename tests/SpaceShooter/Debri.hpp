#pragma once
#include <ag/graphics/Model.hpp>
#include <ag/object/Component.hpp>
#include <ag/object/GameObject.hpp>

class Debri : public ag::Component {
public:
    explicit Debri(const ag::GameObject::Instance& gameObject);
    void update(const ag::InputState& input, float deltaTime) override;
    void draw(const ag::Renderer::Instance& renderer) override;

    void setModel(const ag::Model::Instance& model);
    ag::Model::Instance getModel() const;

private:
    ag::Model::Instance m_model;
};