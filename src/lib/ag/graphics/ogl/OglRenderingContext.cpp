#ifdef AG_OPEN_GL
#include <ag/graphics/IShader.hpp>
#include <ag/graphics/ogl/OglBuffer.hpp>
#include <ag/graphics/ogl/OglRenderingContext.hpp>
#include <ag/graphics/ogl/OglShader.hpp>
#include <ag/graphics/ogl/OglShaderLayout.hpp>
#include <ag/graphics/ogl/OglTexture.hpp>
#include <stdexcept>

namespace ag {
OglRenderingContext::OglRenderingContext()
    : m_vao()
{
}

OglRenderingContext::~OglRenderingContext()
{
    release();
}
void OglRenderingContext::draw(const std::shared_ptr<IShader>& shader, PrimitiveType primitiveType, int primCount)
{
    GLenum primType = convPrimitiveType(primitiveType);
    size_t indexLen = m_indexLength;
    beginVAO(shader);
    if (indexLen > 0) {
        glDrawElements(primType, indexLen, GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(primType, 0, primCount);
    }
    endVAO(shader);
}
// private
void OglRenderingContext::beginVAO(const std::shared_ptr<IShader>& shader)
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
        if (m_isUsingTexCoord) {
            auto oglTexture = std::static_pointer_cast<OglTexture>(m_parameter->getTexture());
            if (m_vertexComponent == 2) {
                oglVertex->bindAsVertex(OglShaderLayout::k_attribVertexIndex, m_vertexComponent, sizeof(VertexData2D), nullptr);
                oglVertex->bindAsVertex(OglShaderLayout::k_attribTexCoordIndex, 2, sizeof(VertexData2D), (const void*)sizeof(glm::vec2));
            } else if (m_vertexComponent == 3) {
                oglVertex->bindAsVertex(OglShaderLayout::k_attribVertexIndex, m_vertexComponent, sizeof(VertexData3D), nullptr);
                oglVertex->bindAsVertex(OglShaderLayout::k_attribTexCoordIndex, 2, sizeof(VertexData3D), (const void*)sizeof(glm::vec3));
            } else {
                throw std::runtime_error("unsupported component.");
            }
            oglTexture->use();
        } else {
            oglVertex->bindAsVertex(OglShaderLayout::k_attribVertexIndex, m_vertexComponent, 0, nullptr);
        }
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
void OglRenderingContext::endVAO(const std::shared_ptr<IShader>& shader)
{
    auto oglShader = std::static_pointer_cast<OglShader>(shader);
    auto oglVertex = std::static_pointer_cast<OglBuffer>(m_vertex);
    auto oglIndex = std::static_pointer_cast<OglBuffer>(m_index);
    if (m_isUsingTexCoord) {
        auto oglTexture = std::static_pointer_cast<OglTexture>(m_parameter->getTexture());
        oglTexture->unuse();
    }
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
GLenum OglRenderingContext::convPrimitiveType(PrimitiveType type)
{
    switch (type) {
    case PrimitiveType::Polygon:
        return GL_POLYGON;
    case PrimitiveType::Triangles:
        return GL_TRIANGLES;
    case PrimitiveType::LineStrip:
        return GL_LINE_STRIP;
    }
    return GL_TRIANGLES;
}
}
#endif