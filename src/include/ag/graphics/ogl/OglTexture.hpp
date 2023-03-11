#pragma once
#ifdef AG_OPEN_GL
#include <ag/graphics/ITexture.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
class OglTexture : public ITexture {
public:
    explicit OglTexture();
    ~OglTexture();

    void init(int width, int height, const uint8_t* pixels);
    int getWidth() const override;
    int getHeight() const override;

    void use();
    void unuse();

private:
    GLuint m_res;
    int m_width;
    int m_height;
};
}
#endif