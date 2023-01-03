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
void RenderingContext::updateVertex(const glm::vec2* data, int len)
{
    m_vertex->allocate(sizeof(glm::vec2) * len);
    m_vertex->update(data);
    m_vertexLength = len;
}

void RenderingContext::updateVertex(const VertexData2D* data, int len)
{
    m_vertex->allocate(sizeof(VertexData2D) * len);
    m_vertex->update(data);
    m_vertexLength = len;
    m_isUsingTexCoord = true;
}
void RenderingContext::updateIndex(const unsigned int* data, int len)
{
    m_index->allocate(sizeof(unsigned int) * len);
    m_index->update(data);
    m_indexLength = len;
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