#pragma once
#include <ag/graphics/RenderingContext.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
class OglRenderingContext : public RenderingContext {
public:
    explicit OglRenderingContext();
    ~OglRenderingContext();
    void setup(const std::shared_ptr<IShader>& shader) override;
    void teardown() override;

private:
    void release();
    GLuint* m_vao;
};
}