#pragma once
#include <ag/graphics/Renderer.hpp>
#include <ag/input/InputState.hpp>
#include <ag/object/Component.hpp>
#include <memory>
#include <string>
#include <vector>

namespace ag {
class GameObject : public std::enable_shared_from_this<GameObject> {
public:
    using Instance = std::shared_ptr<GameObject>;

    static Instance create(const std::string& name);
    void update(const ag::InputState& input, float deltaTime);
    void draw(const ag::Renderer::Instance& renderer);

    void addComponent(const Component::Instance& c);

    template <typename T>
    std::vector<std::shared_ptr<T>> getComponents() const
    {
        std::vector<std::shared_ptr<T>> ret;
        for (Component::Instance c : m_components) {
            auto dc = std::dynamic_pointer_cast<T>(c);
            if (dc) {
                ret.emplace_back(dc);
            }
        }
        return ret;
    }

    template <typename T>
    std::shared_ptr<T> getComponent() const
    {
        std::vector<std::shared_ptr<T>> v = getComponents<T>();
        if (v.empty()) {
            return nullptr;
        }
        return v.front();
    }

    void removeComponent(const Component::Instance& c);
    std::vector<Component::Instance> getComponents() const;

    void setName(const std::string& name);
    std::string getName() const;

    void setTag(const std::string& tag);
    std::string getTag() const;

    void setPosition(const glm::vec3& position);
    glm::vec3 getPosition() const;

    void setRotation(const glm::vec3& rotation);
    glm::vec3 getRotation() const;

    void setScale(const glm::vec3& scale);
    glm::vec3 getScale() const;

    void destroy();
    bool isDestroyed() const;

private:
    GameObject();
    std::vector<Component::Instance> m_components;
    std::string m_name;
    std::string m_tag;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
    bool m_isDestroyed;
};
}