#include <ag/graphics/ogl/OglShader.hpp>
#include <ag/graphics/ogl/OglShaderCompiler.hpp>
#include <ag/native/glfw.hpp>
#include <iostream>

namespace ag {
std::shared_ptr<IShader> OglShaderCompiler::compileFromPartedSource(const std::string& vSource, const std::string& fSource)
{
    GLuint program = glCreateProgram();
    if (program == 0) {
        throw std::runtime_error("failed a create program");
    }
    GLuint vShader = compileFunction(vSource, GL_VERTEX_SHADER);
    GLuint fShader = compileFunction(fSource, GL_FRAGMENT_SHADER);
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (GL_FALSE == status) {
        reportProgramError(program);
    }
    return std::make_shared<OglShader>(program);
}
bool OglShaderCompiler::isCompilableFromPartedSource() const
{
    return true;
}
std::shared_ptr<IShader> OglShaderCompiler::compileFromSingleFile(const std::string& file)
{
    return nullptr;
}
std::shared_ptr<IShader> OglShaderCompiler::compileFromSingleSource(const std::string& source) { return nullptr; }
bool OglShaderCompiler::isCompilableFromSingleSource() const { return false; }

bool OglShaderCompiler::isCompilableFromSingleFile() const
{
    return false;
}
// private
GLuint OglShaderCompiler::compileFunction(const std::string& source, GLenum type)
{
    // compile shader
    GLuint shader = glCreateShader(type);
    if (shader == 0) {
        reportFunctionError(shader, type);
        return 0;
    }
    const char* sourceC = source.c_str();
    glShaderSource(shader, 1, &sourceC, NULL);
    glCompileShader(shader);
    // check status
    GLint compileErr;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileErr);
    if (GL_FALSE == compileErr) {
        reportFunctionError(shader, type);
    }
    return shader;
}
void OglShaderCompiler::reportFunctionError(GLuint shader, GLenum type)
{
    std::string baseStr;
    if (type == GL_VERTEX_SHADER) {
        baseStr = "failed a create vertex shader";
    } else if (type == GL_FRAGMENT_SHADER) {
        baseStr = "failed a create vertex shader";
    }
    GLsizei logSize;
    GLsizei bufSize = 2048;
    char buf[2048] = { 0 };
    glGetShaderInfoLog(shader, bufSize, &logSize, buf);
    std::string str = baseStr + '\n' + buf;
    std::cerr << str << std::endl;
    throw std::runtime_error(str);
}
void OglShaderCompiler::reportProgramError(GLuint program)
{
    // http://marina.sys.wakayama-u.ac.jp/~tokoi/?date=20101208
    GLsizei bufSize;

    /* シェーダのリンク時のログの長さを取得する */
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);

    if (bufSize > 1) {
        GLchar* infoLog = (GLchar*)malloc(bufSize);

        if (infoLog != NULL) {
            GLsizei length;

            /* シェーダのリンク時のログの内容を取得する */
            glGetProgramInfoLog(program, bufSize, &length, infoLog);
            std::cerr << "InfoLog:" << std::endl;
            std::cerr << infoLog << std::endl;
            std::string infoLogString = std::string(infoLog);
            free(infoLog);
            throw std::runtime_error(infoLogString);
        } else
            std::cerr << "Could not allocate InfoLog buffer."
                      << std::endl;
    }
}
}