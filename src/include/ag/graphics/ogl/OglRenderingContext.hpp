#pragma once
#ifdef AG_OPEN_GL
#include <ag/graphics/RenderingContext.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
class OglRenderingContext : public RenderingContext {
public:
    explicit OglRenderingContext();
    ~OglRenderingContext();
    //void setup(const std::shared_ptr<IShader>& shader) override;
    //void teardown(const std::shared_ptr<IShader>& shader) override;
    void draw(const std::shared_ptr<IShader>& shader, PrimitiveType primitiveType, int primCount) override;

private:
    void release();
    GLuint m_vao;
};
}
#endif