#include <ag/Engine.hpp>
#include <ag/graphics/FontSprite.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/IRenderFunction.hpp>
#include <ag/graphics/ITexture.hpp>
#include <ag/graphics/Renderer.hpp>

namespace ag {
Renderer::Renderer()
    : m_projMat()
    , m_colorDrawRectObject(RenderingObject::createColorRectangle(false))
    , m_colorFillRectObject(RenderingObject::createColorRectangle(true))
    , m_colorDrawCircleObject(RenderingObject::createColorCircle(false))
    , m_colorFillCircleObject(RenderingObject::createColorCircle(true))
    , m_textureObject(RenderingObject::createTextureRectangle())
    , m_stringObject(RenderingObject::createString())
    , m_fontMap()
{
}

void Renderer::resize(int width, int height)
{
    float fWidth = static_cast<float>(width);
    float fHeight = static_cast<float>(height);
    m_projMat = glm::ortho(0.0f, fWidth, fHeight, 0.0f /* lrbt*/, -1.0f, 1.0f);
}
void Renderer::resize(const glm::ivec2& size)
{
    resize(size.x, size.y);
}
void Renderer::drawTexture(const glm::vec2& pos, const glm::vec2& size, const std::shared_ptr<ITexture>& texture)
{
    auto param = m_textureObject->getContext()->getParameter();
    glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0)),
        glm::vec3(size, 1));
    param->setTransform(m_projMat * transform);
    param->setTexture(texture);
    ag::Engine::getInstance()->getGraphicsDriver()->getRenderFunction()->draw(m_textureObject);
}
void Renderer::drawTexture(const glm::vec2& pos, const std::shared_ptr<ITexture>& texture)
{
    drawTexture(pos, glm::vec2(texture->getWidth(), texture->getHeight()), texture);
}
void Renderer::drawRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
{
    auto param = m_colorDrawRectObject->getContext()->getParameter();
    glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0)),
        glm::vec3(size, 1));
    param->setTransform(m_projMat * transform);
    param->setColor1(color);
    ag::Engine::getInstance()->getGraphicsDriver()->getRenderFunction()->draw(m_colorDrawRectObject);
}
void Renderer::fillRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
{
    auto param = m_colorFillRectObject->getContext()->getParameter();
    glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0)),
        glm::vec3(size, 1));
    param->setTransform(m_projMat * transform);
    param->setColor1(color);
    ag::Engine::getInstance()->getGraphicsDriver()->getRenderFunction()->draw(m_colorFillRectObject);
}

void Renderer::drawCircle(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
{
    auto param = m_colorDrawCircleObject->getContext()->getParameter();
    glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0)),
        glm::vec3(size / 2.f, 1));
    param->setTransform(m_projMat * transform);
    param->setColor1(color);
    ag::Engine::getInstance()->getGraphicsDriver()->getRenderFunction()->draw(m_colorDrawCircleObject);
}
void Renderer::fillCircle(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
{
    auto param = m_colorFillCircleObject->getContext()->getParameter();
    glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0)),
        glm::vec3(size / 2.f, 1));
    param->setTransform(m_projMat * transform);
    param->setColor1(color);
    ag::Engine::getInstance()->getGraphicsDriver()->getRenderFunction()->draw(m_colorFillCircleObject);
}
void Renderer::drawChar(const glm::vec2& pos, int fontSize, unsigned long charcode, const glm::vec4& color)
{
    if (!m_fontMap) {
        return;
    }
    auto sprite = m_fontMap->load(fontSize, charcode);
    auto param = m_stringObject->getContext()->getParameter();
    glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0)),
        glm::vec3(sprite->metrics.size, 1));
    param->setTransform(m_projMat * transform);
    param->setTexture(sprite->texture);
    param->setColor1(color);
    ag::Engine::getInstance()->getGraphicsDriver()->getRenderFunction()->draw(m_stringObject);
}
void Renderer::drawString(const glm::vec2& pos, int fontSize, const std::u16string& str, const glm::vec4& color) { }
void Renderer::setFontMap(const std::shared_ptr<FontMap>& fontMap) { m_fontMap = fontMap; }
std::shared_ptr<FontMap> Renderer::getFontMap() const { return m_fontMap; }
}