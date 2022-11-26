#pragma once
#include <ag/graphics/RenderingContext.hpp>
#include <ag/native/glm.hpp>
#include <memory>

namespace ag {
class IShader;
class Renderer {
public:
    explicit Renderer();

    void resize(int width, int height);
    void resize(const glm::ivec2& size);
    void drawRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);

private:
    static RenderingContext::Instance createRenderingContext();
    glm::mat4 m_projMat;
    //glm::vec4 m_color;

    std::shared_ptr<IShader> m_colorRectShader;
    RenderingContext::Instance m_colorRectCtx;
};
}