#include <ag/graphics/IShader.hpp>
#include <ag/graphics/ogl/OglBuffer.hpp>
#include <ag/graphics/ogl/OglRenderingContext.hpp>
#include <ag/graphics/ogl/OglShader.hpp>

namespace ag {
OglRenderingContext::OglRenderingContext()
    : m_vao()
{
}

OglRenderingContext::~OglRenderingContext()
{
    release();
}

void OglRenderingContext::setup(const std::shared_ptr<IShader>& shader)
{
    auto oglShader = std::static_pointer_cast<OglShader>(shader);
    auto oglVertex = std::static_pointer_cast<OglBuffer>(m_vertex);
    auto oglIndex = std::static_pointer_cast<OglBuffer>(m_index);
    if (!m_vao) {
        glGenVertexArraysAPPLE(1, &m_vao);
        glBindVertexArrayAPPLE(m_vao);
        oglVertex->bindAsVertex(0, 2, 0, nullptr);
        oglIndex->bindAsIndex();
    } else {
        glBindVertexArrayAPPLE(m_vao);
        oglIndex->bindAsIndex();
    }
    oglShader->use();
    oglShader->apply(m_parameter);
}
void OglRenderingContext::teardown(const std::shared_ptr<IShader>& shader)
{
    auto oglShader = std::static_pointer_cast<OglShader>(shader);
    auto oglVertex = std::static_pointer_cast<OglBuffer>(m_vertex);
    auto oglIndex = std::static_pointer_cast<OglBuffer>(m_index);
    oglShader->unuse();
    oglVertex->unbindAsVertex();
    oglIndex->unbindAsIndex();
    glBindVertexArrayAPPLE(0);
}
// private
void OglRenderingContext::release()
{
    if (m_vao) {
        glDeleteVertexArraysAPPLE(1, &m_vao);
        m_vao = 0;
    }
}
}