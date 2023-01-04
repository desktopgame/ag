#pragma once
#include <ag/graphics/Camera.hpp>
#include <ag/graphics/IShader.hpp>
#include <ag/graphics/Mesh.hpp>
#include <ag/native/glm.hpp>
#include <memory>
#include <string>
#include <vector>

namespace ag {
class Node {
public:
    using Instance = std::shared_ptr<Node>;
    explicit Node(const std::weak_ptr<Node> parent, const std::string& name);

    void addMesh(const std::shared_ptr<Mesh>& mesh);
    void addNode(const std::shared_ptr<Node>& node);
    void draw(const std::shared_ptr<IShader>& shader, const Camera& camera, const glm::mat4& transform);
    void drawWithLight(const std::shared_ptr<IShader>& shader, const Camera& camera, const glm::mat4& transform);

    std::string getName() const;

    void setTransform(const glm::mat4& transform);
    glm::mat4 getTransform() const;

private:
    std::weak_ptr<Node> m_parent;
    std::string m_name;
    glm::mat4 m_transform;
    std::vector<std::shared_ptr<Mesh>> m_meshes;
    std::vector<std::shared_ptr<Node>> m_children;
};
}