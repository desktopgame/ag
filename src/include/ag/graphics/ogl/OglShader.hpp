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

private:
    GLuint m_program;
    GLuint m_attribVertexPosition;
    GLuint m_attribTexCoordPosition;
    GLuint m_uniformTransformMatrix;
    GLuint m_uniformTexture;
    GLuint m_uniformColor1;
    GLuint m_uniformColor2;
};
}
#endif