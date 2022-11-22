#include <ag/graphics/ogl/OglBuffer.hpp>

namespace ag {

OglBuffer::OglBuffer()
    : m_res(nullptr)
    , m_size(0)
{
    release();
}
void OglBuffer::allocate(size_t size)
{
    if (!m_res) {
        glGenBuffers(1, m_res);
    }
    m_size = size;
}
void OglBuffer::update(const void* data)
{
    glBindBuffer(GL_ARRAY_BUFFER, *m_res);
    glBufferData(GL_ARRAY_BUFFER, m_size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void OglBuffer::release()
{
    if (m_res) {
        glDeleteBuffers(1, m_res);
        m_res = nullptr;
    }
}
}