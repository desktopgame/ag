#include <ag/graphics/ogl/OglShader.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ag {
OglShader::OglShader(GLuint program)
    : m_program(program)
    , m_attribVertexPosition()
    , m_attribTexCoordPosition()
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
    // get variable location
    if (!m_attribVertexPosition) {
        m_attribVertexPosition = glGetAttribLocation(m_program, "aVertex");
    }
    if (!m_attribTexCoordPosition) {
        m_attribTexCoordPosition = glGetAttribLocation(m_program, "aTexCoord");
    }
    if (!m_uniformTransformMatrix) {
        m_uniformTransformMatrix = glGetUniformLocation(m_program, "uTransformMatrix");
    }
    if (!m_uniformTexture) {
        m_uniformTexture = glGetUniformLocation(m_program, "uTexture");
    }
    if (!m_uniformColor1) {
        m_uniformColor1 = glGetUniformLocation(m_program, "uColor1");
    }
    if (!m_uniformColor2) {
        m_uniformColor2 = glGetUniformLocation(m_program, "uColor2");
    }
    // apply values
    glUniformMatrix4fv(m_uniformTransformMatrix, 1, GL_FALSE, glm::value_ptr(parameter->getTransform()));
    if (parameter->useTexture()) {
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