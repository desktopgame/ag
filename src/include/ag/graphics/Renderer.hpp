#pragma once
#include <ag/graphics/FontMap.hpp>
#include <ag/graphics/RenderingContext.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/native/glm.hpp>
#include <memory>

namespace ag {
class IShader;
class ITexture;
class FontMap;
class Renderer {
public:
    explicit Renderer();

    void resize(int width, int height);
    void resize(const glm::ivec2& size);
    void drawTexture(const glm::vec2& pos, const glm::vec2& size, const std::shared_ptr<ITexture>& texture, const glm::vec4& color);
    void drawTexture(const glm::vec2& pos, const std::shared_ptr<ITexture>& texture, const glm::vec4& color);
    void drawRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
    void fillRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
    void drawCircle(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
    void fillCircle(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
    void drawChar(const glm::vec2& pos, int fontSize, unsigned long charcode, const glm::vec4& color);
    void drawString(const glm::vec2& pos, int fontSize, const std::u16string& str, const glm::vec4& color);
    glm::vec2 measureString(int fontSize, const std::u16string& str);

    void setFontMap(const std::shared_ptr<FontMap>& fontMap);
    std::shared_ptr<FontMap> getFontMap() const;

private:
    static void draw(const RenderingObject::Instance& obj);
    glm::mat4 m_projMat;
    RenderingObject::Instance m_colorDrawRectObject;
    RenderingObject::Instance m_colorFillRectObject;
    RenderingObject::Instance m_colorDrawCircleObject;
    RenderingObject::Instance m_colorFillCircleObject;
    RenderingObject::Instance m_textureObject;
    RenderingObject::Instance m_stringObject;
    std::shared_ptr<FontMap> m_fontMap;
};
}