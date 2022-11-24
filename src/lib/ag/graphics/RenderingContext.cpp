#include <ag/graphics/IBuffer.hpp>
#include <ag/graphics/RenderingContext.hpp>

namespace ag {
RenderingContext::RenderingContext()
    : m_parameter()
    , m_vertex()
    , m_index()
    , m_vertexLength()
    , m_indexLength()
{
}
void RenderingContext::updateVertex(const std::vector<glm::vec3>& data)
{
    m_vertex->allocate(sizeof(glm::vec3) * data.size());
    m_vertex->update(&data.front().x);
    m_vertexLength = data.size();
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
}