#include <ag/Engine.hpp>
#include <ag/graphics/IBuffer.hpp>
#include <ag/graphics/IGraphicsDevice.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/RenderingContext.hpp>

namespace ag {
RenderingContext::RenderingContext()
    : m_parameter(std::make_shared<ShaderParameter>())
    , m_vertex(Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice()->newVertexBuffer())
    , m_index(Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice()->newIndexBuffer())
    , m_vertexLength()
    , m_indexLength()
    , m_isUsingTexCoord(false)
{
}
void RenderingContext::updateVertex(const std::vector<glm::vec2>& data)
{
    m_vertex->allocate(sizeof(glm::vec2) * data.size());
    m_vertex->update(&data.front().x);
    m_vertexLength = data.size();
}

void RenderingContext::updateVertex(const std::vector<VertexData>& data)
{
    m_vertex->allocate(sizeof(VertexData) * data.size());
    m_vertex->update(&data.front().position.x);
    m_vertexLength = data.size();
    m_isUsingTexCoord = true;
}
void RenderingContext::updateIndex(const std::vector<unsigned short>& data)
{
    m_index->allocate(sizeof(unsigned short) * data.size());
    m_index->update(&data.front());
    m_indexLength = data.size();
}

size_t RenderingContext::getVertexLength() const
{
    return m_vertexLength;
}
size_t RenderingContext::getIndexLength() const
{
    return m_indexLength;
}
std::shared_ptr<ShaderParameter> RenderingContext::getParameter() const
{
    return m_parameter;
}
}