#ifdef AG_OPEN_GL
#include <ag/graphics/ogl/OglTexture.hpp>

namespace ag {
OglTexture::OglTexture()
    : m_res()
    , m_width()
    , m_height()
{
    glGenTextures(1, &m_res);

    glBindTexture(GL_TEXTURE_2D, m_res);
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenerateMipmap(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}
OglTexture::~OglTexture()
{
    if (m_res) {
        glDeleteTextures(1, &m_res);
        m_res = 0;
    }
}
void OglTexture::update(int width, int height, const uint8_t* pixels)
{

    unsigned int size = GL_UNSIGNED_BYTE;
    glBindTexture(GL_TEXTURE_2D, m_res);
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, size, pixels);
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_width = width;
    m_height = height;
}
size_t OglTexture::getWidth() const { return m_width; }
size_t OglTexture::getHeight() const { return m_height; }
}
#endif