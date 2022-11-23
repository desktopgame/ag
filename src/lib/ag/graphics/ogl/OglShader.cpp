#include <ag/graphics/ogl/OglShader.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ag {
OglShader::OglShader(GLuint program)
    : m_program(program)
{
}

OglShader::~OglShader()
{
    glDeleteProgram(m_program);
}

void OglShader::apply(const std::shared_ptr<IShaderParameter>& parameter)
{
    glUseProgram(m_program);
    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(parameter->getTransform()));
    if (parameter->useTexture()) {
        glUniform1i(1, 0);
    }
    if (parameter->useColor1()) {
        glm::vec4 color1 = parameter->getColor1();
        glUniform4fv(2, 1, &color1.x);
    }
    if (parameter->useColor2()) {
        glm::vec4 color2 = parameter->getColor1();
        glUniform4fv(3, 1, &color2.x);
    }
    glUseProgram(0);
}
}