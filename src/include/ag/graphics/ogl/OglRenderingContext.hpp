#pragma once
#ifdef AG_OPEN_GL
#include <ag/graphics/RenderingContext.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
class OglRenderingContext : public RenderingContext {
public:
    explicit OglRenderingContext();
    ~OglRenderingContext();
    void draw(const std::shared_ptr<IShader>& shader, PrimitiveType primitiveType, int primCount) override;

private:
    void beginVAO(const std::shared_ptr<IShader>& shader);
    void endVAO(const std::shared_ptr<IShader>& shader);
    void release();
    static GLenum convPrimitiveType(PrimitiveType type);
    GLuint m_vao;
};
}
#endif