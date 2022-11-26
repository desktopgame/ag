#pragma once
#include <ag/graphics/IShaderCompiler.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
class OglShaderCompiler : public IShaderCompiler {
public:
    OglShaderCompiler() = default;
    ~OglShaderCompiler() = default;

    std::shared_ptr<IShader> compileFromPartedSource(const std::string& vSource, const std::string& fSource) override;
    bool isCompilableFromPartedSource() const override;

    std::shared_ptr<IShader> compileFromSingleFile(const std::string& file) override;
    bool isCompilableFromSingleFile() const override;

private:
    GLuint compileFunction(const std::string& source, GLenum type);
    void reportFunctionError(GLuint shader, GLenum type);
    void reportProgramError(GLuint program);
};
}