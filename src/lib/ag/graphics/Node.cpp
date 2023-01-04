#include <ag/graphics/Node.hpp>

namespace ag {
Node::Node(const std::weak_ptr<Node> parent, const std::string& name)
    : m_parent(parent)
    , m_name(name)
    , m_transform(1.0f)
    , m_meshes()
    , m_children()
{
}

void Node::addMesh(const std::shared_ptr<Mesh>& mesh) { m_meshes.push_back(mesh); }
void Node::addNode(const std::shared_ptr<Node>& node) { m_children.push_back(node); }
void Node::draw(const std::shared_ptr<IShader>& shader, const Camera& camera, const glm::mat4& transform)
{
    glm::mat4 newTransform = transform * m_transform;
    for (auto msh : m_meshes) {
        msh->draw(shader, camera, newTransform);
    }
    for (auto child : m_children) {
        child->draw(shader, camera, newTransform);
    }
}

void Node::drawWithLight(const std::shared_ptr<IShader>& shader, const Camera& camera, const glm::mat4& transform)
{
    glm::mat4 newTransform = transform * m_transform;
    for (auto msh : m_meshes) {
        msh->drawWithLight(shader, camera, newTransform);
    }
    for (auto child : m_children) {
        child->drawWithLight(shader, camera, newTransform);
    }
}

std::string Node::getName() const { return m_name; }
void Node::setTransform(const glm::mat4& transform) { m_transform = transform; }
glm::mat4 Node::getTransform() const { return m_transform; }
}