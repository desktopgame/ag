#ifdef AG_OPEN_GL
#include <ag/graphics/ogl/OglShader.hpp>
#include <ag/graphics/ogl/OglShaderLayout.hpp>
#include <ag/graphics/ogl/OglTexture.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ag {
OglShader::OglShader(GLuint program)
    : m_program(program)
    , m_uniformTransformMatrix()
    , m_uniformTexture()
    , m_uniformColor1()
    , m_uniformColor2()
{
}

OglShader::~OglShader()
{
    glDeleteProgram(m_program);
}

void OglShader::apply(const std::shared_ptr<ShaderParameter>& parameter)
{
    // bind attribute location
    glBindAttribLocation(m_program, OglShaderLayout::k_attribVertexIndex, OglShaderLayout::k_attribVertexName);
    glBindAttribLocation(m_program, OglShaderLayout::k_attribTexCoordIndex, OglShaderLayout::k_attribTexCoordName);
    // get variable location
    if (!m_uniformTransformMatrix) {
        m_uniformTransformMatrix = glGetUniformLocation(m_program, OglShaderLayout::k_uniformTransformName);
    }
    if (!m_uniformTexture) {
        m_uniformTexture = glGetUniformLocation(m_program, OglShaderLayout::k_uniformTextureName);
    }
    if (!m_uniformColor1) {
        m_uniformColor1 = glGetUniformLocation(m_program, OglShaderLayout::k_uniformColor1Name);
    }
    if (!m_uniformColor2) {
        m_uniformColor2 = glGetUniformLocation(m_program, OglShaderLayout::k_uniformColor2Name);
    }
    // apply values
    glUniformMatrix4fv(m_uniformTransformMatrix, 1, GL_FALSE, glm::value_ptr(parameter->getTransform()));
    if (parameter->useTexture()) {
        auto oglTexture = std::static_pointer_cast<OglTexture>(parameter->getTexture());
        oglTexture->use();
        glUniform1i(m_uniformTexture, 0);
    }
    if (parameter->useColor1()) {
        glm::vec4 color1 = parameter->getColor1();
        glUniform4fv(m_uniformColor1, 1, &color1.x);
    }
    if (parameter->useColor2()) {
        glm::vec4 color2 = parameter->getColor1();
        glUniform4fv(m_uniformColor2, 1, &color2.x);
    }
}
void OglShader::use() { glUseProgram(m_program); }
void OglShader::unuse() { glUseProgram(0); }
}
#endif