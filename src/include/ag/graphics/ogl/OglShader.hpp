#pragma once
#ifdef AG_OPEN_GL
#include <ag/graphics/IShader.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
class OglShader : public IShader {
public:
    explicit OglShader(GLuint program);
    ~OglShader();
    void apply(const std::shared_ptr<ShaderParameter>& parameter) override;

    void use();
    void unuse();

    GLuint getAttribVertex() const;
    GLuint getAttribTexCoord() const;

private:
    GLuint m_program;
    GLuint m_uniformTransformMatrix;
    GLuint m_uniformTexture;
    GLuint m_uniformColor;
    GLuint m_attribVertex;
    GLuint m_attribTexCoord;
};
}
#endif