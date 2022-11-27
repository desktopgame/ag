#pragma once
#ifdef AG_OPEN_GL
#include <ag/graphics/ITexture.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
class OglTexture : public ITexture {
public:
    explicit OglTexture();
    ~OglTexture();

    void update(int width, int height, const uint8_t* pixels) override;
    size_t getWidth() const override;
    size_t getHeight() const override;

private:
    GLuint m_res;
    int m_width;
    int m_height;
};
}
#endif