#pragma once
#include <ag/graphics/IShader.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
class OglShader : public IShader {
public:
    explicit OglShader(GLuint program);
    ~OglShader();
    void apply(const std::shared_ptr<ShaderParameter>& parameter) override;

private:
    GLuint m_program;
};
}