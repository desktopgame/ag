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
#if __APPLE__
        if (GLEW_APPLE_vertex_array_object) {
            glGenVertexArraysAPPLE(1, &m_vao);
            glBindVertexArrayAPPLE(m_vao);
        } else
#endif
        {
            glGenVertexArrays(1, &m_vao);
            glBindVertexArray(m_vao);
        }
        oglVertex->bindAsVertex(0, 2, 0, nullptr);
        oglIndex->bindAsIndex();
    } else {
#if __APPLE__
        if (GLEW_APPLE_vertex_array_object) {
            glBindVertexArrayAPPLE(m_vao);
        } else
#endif
        {
            glBindVertexArray(m_vao);
        }
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
#if __APPLE__
    if (GLEW_APPLE_vertex_array_object) {
        glBindVertexArrayAPPLE(0);
    } else
#endif
    {
        glBindVertexArray(0);
    }
}
// private
void OglRenderingContext::release()
{
    if (m_vao) {
#if __APPLE__
        if (GLEW_APPLE_vertex_array_object) {
            glDeleteVertexArraysAPPLE(1, &m_vao);
        } else
#endif
        {
            glDeleteVertexArrays(1, &m_vao);
        }
        m_vao = 0;
    }
}
}