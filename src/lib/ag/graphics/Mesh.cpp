#include <ag/Engine.hpp>
#include <ag/graphics/IGraphicsDevice.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/Mesh.hpp>

namespace ag {
Mesh::Mesh(const std::string& name, int primCount)
    : m_name(name)
    , m_primCount(primCount)
    , m_material(std::make_shared<Material>())
    , m_renderingContext(ag::Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice()->newRenderingContext())
{
}

void Mesh::updateVertex(const glm::vec3* data, int len) { m_renderingContext->updateVertex(data, len); }
void Mesh::updateVertex(const VertexData3D* data, int len) { m_renderingContext->updateVertex(data, len); }
void Mesh::updateIndex(const unsigned int* data, int len) { m_renderingContext->updateIndex(data, len); }
void Mesh::draw(const std::shared_ptr<IShader>& shader, const Camera& camera, const glm::mat4& transform)
{
    auto param = m_renderingContext->getParameter();
    param->setTransform(camera.getProjectionMatrix() * camera.getViewMatrix() * transform);
    param->setColor(m_material->diffuse);
    m_renderingContext->draw(shader, ag::PrimitiveType::Triangles, m_primCount);
}

void Mesh::drawWithLight(const std::shared_ptr<IShader>& shader, const Camera& camera, const glm::mat4& transform)
{
    auto param = m_renderingContext->getParameter();
    param->setTransform(camera.getProjectionMatrix() * camera.getViewMatrix() * transform);
    param->setColor(m_material->diffuse);
    m_renderingContext->draw(shader, ag::PrimitiveType::Triangles, m_primCount);
}
std::shared_ptr<Material> Mesh::getMaterial() const { return m_material; }
}