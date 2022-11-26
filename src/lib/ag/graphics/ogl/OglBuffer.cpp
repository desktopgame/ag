#include <ag/graphics/ogl/OglBuffer.hpp>

namespace ag {

OglBuffer::OglBuffer(bool indexMode)
    : m_res()
    , m_size(0)
    , m_indexMode(indexMode)
{
    release();
}
void OglBuffer::allocate(size_t size)
{
    if (!m_res) {
        glGenBuffers(1, &m_res);
    }
    m_size = size;
}
void OglBuffer::update(const void* data)
{
    GLenum mode = m_indexMode ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER;
    glBindBuffer(mode, m_res);
    glBufferData(mode, m_size, data, GL_STATIC_DRAW);
    glBindBuffer(mode, 0);
}
void OglBuffer::release()
{
    if (m_res) {
        glDeleteBuffers(1, &m_res);
        m_res = 0;
    }
}
void OglBuffer::bindAsVertex(GLuint attrib, GLint component, GLsizei stride, const void* offset)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_res);
    glVertexAttribPointer(attrib, component, GL_FLOAT, GL_FALSE, 0, offset);
    glEnableVertexAttribArray(attrib);
}
void OglBuffer::unbindAsVertex()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void OglBuffer::bindAsIndex()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_res);
}
void OglBuffer::unbindAsIndex()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}