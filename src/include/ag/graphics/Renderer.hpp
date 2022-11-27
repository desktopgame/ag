#pragma once
#include <ag/graphics/RenderingContext.hpp>
#include <ag/graphics/RenderingObject.hpp>
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
    void fillRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
    void drawCircle(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
    void fillCircle(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);

private:
    glm::mat4 m_projMat;

    RenderingObject::Instance m_colorDrawRectObject;
    RenderingObject::Instance m_colorFillRectObject;
    RenderingObject::Instance m_colorDrawCircleObject;
    RenderingObject::Instance m_colorFillCircleObject;
    RenderingObject::Instance m_textureObject;
};
}