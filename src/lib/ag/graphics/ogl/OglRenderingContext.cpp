#include <ag/graphics/ogl/OglBuffer.hpp>
#include <ag/graphics/ogl/OglRenderingContext.hpp>

namespace ag {
OglRenderingContext::OglRenderingContext()
    : m_vao(nullptr)
{
}

OglRenderingContext::~OglRenderingContext()
{
    release();
}

void OglRenderingContext::setup(const std::shared_ptr<IShader>& shader)
{
    auto oglVertex = std::static_pointer_cast<OglBuffer>(m_vertex);
    auto oglIndex = std::static_pointer_cast<OglBuffer>(m_index);
    if (!m_vao) {
        glGenVertexArrays(1, m_vao);
        glBindVertexArray(*m_vao);
        oglVertex->bindAsVertex(0, 3, sizeof(float) * 3, 0);
        oglIndex->bindAsIndex();
    } else {
        glBindVertexArray(*m_vao);
    }
}
void OglRenderingContext::teardown()
{
    auto oglVertex = std::static_pointer_cast<OglBuffer>(m_vertex);
    auto oglIndex = std::static_pointer_cast<OglBuffer>(m_index);
    oglVertex->unbindAsVertex();
    oglIndex->unbindAsIndex();
    glBindVertexArray(0);
}
// private
void OglRenderingContext::release()
{
    if (m_vao) {
        glDeleteVertexArrays(1, m_vao);
        m_vao = nullptr;
    }
}
}