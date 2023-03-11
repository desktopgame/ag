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
void OglTexture::init(int width, int height, const uint8_t* pixels)
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
int OglTexture::getWidth() const { return m_width; }
int OglTexture::getHeight() const { return m_height; }

void OglTexture::use()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_res);
    glEnable(GL_TEXTURE_2D);
}
void OglTexture::unuse()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}
}
#endif