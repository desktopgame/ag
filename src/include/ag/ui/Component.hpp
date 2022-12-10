#pragma once
#include <ag/graphics/Renderer.hpp>
#include <ag/native/glm.hpp>
#include <memory>

namespace agui {
class Container;
class Component : public std::enable_shared_from_this<Component> {
public:
    using Instance = std::shared_ptr<Component>;
    explicit Component() = default;
    virtual ~Component() = default;

    virtual void update(const std::shared_ptr<ag::Renderer>& r) = 0;

    void setLocation(const glm::ivec2& location);
    glm::ivec2 getLocation() const;

    void setSize(const glm::ivec2& size);
    glm::ivec2 getSize() const;

    void setMinimumSize(const glm::ivec2& minimumSize);
    glm::ivec2 getMinimumSize() const;

    void setPreferredSize(const glm::ivec2& preferredSize);
    glm::ivec2 getPreferredSize() const;

    void setMaximumSize(const glm::ivec2& maximumSize);
    glm::ivec2 getMaximumSize() const;

    void setParent(const std::weak_ptr<Container>& parent);
    std::weak_ptr<Container> getParent() const;

private:
    glm::ivec2 m_location;
    glm::ivec2 m_size;
    glm::ivec2 m_minimumSize;
    glm::ivec2 m_preferredSize;
    glm::ivec2 m_maximumSize;
    std::weak_ptr<Container> m_parent;
};
}