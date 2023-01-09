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
    , m_uniformColor()
    , m_attribVertex()
    , m_attribTexCoord()
{
}

OglShader::~OglShader()
{
    glDeleteProgram(m_program);
}

void OglShader::apply(const std::shared_ptr<ShaderParameter>& parameter)
{
    // bind attribute location
    if (!m_attribVertex) {
        m_attribVertex = glGetAttribLocation(m_program, OglShaderLayout::k_attribVertexName);
    }
    if (!m_attribTexCoord) {
        m_attribTexCoord = glGetAttribLocation(m_program, OglShaderLayout::k_attribTexCoordName);
    }
    // get variable location
    if (!m_uniformTransformMatrix) {
        m_uniformTransformMatrix = glGetUniformLocation(m_program, OglShaderLayout::k_uniformTransformName);
    }
    if (!m_uniformTexture) {
        m_uniformTexture = glGetUniformLocation(m_program, OglShaderLayout::k_uniformTextureName);
    }
    if (!m_uniformColor) {
        m_uniformColor = glGetUniformLocation(m_program, OglShaderLayout::k_uniformColorName);
    }
    // apply values
    glUniformMatrix4fv(m_uniformTransformMatrix, 1, GL_FALSE, glm::value_ptr(parameter->getTransform()));
    if (parameter->useTexture()) {
        auto oglTexture = std::static_pointer_cast<OglTexture>(parameter->getTexture());
        oglTexture->use();
        glUniform1i(m_uniformTexture, 0);
    }
    if (parameter->useColor()) {
        glm::vec4 color = parameter->getColor();
        glUniform4fv(m_uniformColor, 1, &color.x);
    }
}
void OglShader::use() { glUseProgram(m_program); }
void OglShader::unuse() { glUseProgram(0); }
GLuint OglShader::getAttribVertex() const { return m_attribVertex; }
GLuint OglShader::getAttribTexCoord() const { return m_attribTexCoord; }
}
#endif