#include <ag/Engine.hpp>
#include <ag/graphics/FontSprite.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/IRenderFunction.hpp>
#include <ag/graphics/ITexture.hpp>
#include <ag/graphics/Renderer.hpp>

namespace ag {
Renderer::Renderer()
    : m_orthoMat()
    , m_colorDrawRectObject(RenderingObject::createColorRectangle(false))
    , m_colorFillRectObject(RenderingObject::createColorRectangle(true))
    , m_colorDrawCircleObject(RenderingObject::createColorCircle(false))
    , m_colorFillCircleObject(RenderingObject::createColorCircle(true))
    , m_textureObject(RenderingObject::createTextureRectangle())
    , m_stringObject(RenderingObject::createString())
    , m_fontMap()
    , m_stack()
{
}

void Renderer::begin(const std::shared_ptr<Window>& window, const RenderPass& pass)
{
    ag::Engine::getInstance()->getGraphicsDriver()->getRenderFunction()->begin(window, pass);
}
void Renderer::end()
{
    ag::Engine::getInstance()->getGraphicsDriver()->getRenderFunction()->end();
}
void Renderer::resize(int width, int height)
{
    float fWidth = static_cast<float>(width);
    float fHeight = static_cast<float>(height);
    m_orthoMat = glm::ortho(0.0f, fWidth, fHeight, 0.0f /* lrbt*/, -1.0f, 1.0f);
}
void Renderer::resize(const glm::ivec2& size)
{
    resize(size.x, size.y);
}
void Renderer::drawTexture(const glm::vec2& pos, const glm::vec2& size, const std::shared_ptr<ITexture>& texture, const glm::vec4& color)
{
    auto param = m_textureObject->getContext()->getParameter();
    glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0)),
        glm::vec3(size, 1));
    param->setTransform(m_orthoMat * (getModelMatrix() * transform));
    param->setTexture(texture);
    param->setColor1(color);
    draw(m_textureObject);
}
void Renderer::drawTexture(const glm::vec2& pos, const std::shared_ptr<ITexture>& texture, const glm::vec4& color)
{
    drawTexture(pos, glm::vec2(texture->getWidth(), texture->getHeight()), texture, color);
}
void Renderer::drawRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
{
    auto param = m_colorDrawRectObject->getContext()->getParameter();
    glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0)),
        glm::vec3(size, 1));
    param->setTransform(m_orthoMat * (getModelMatrix() * transform));
    param->setColor1(color);
    draw(m_colorDrawRectObject);
}
void Renderer::fillRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
{
    auto param = m_colorFillRectObject->getContext()->getParameter();
    glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0)),
        glm::vec3(size, 1));
    param->setTransform(m_orthoMat * (getModelMatrix() * transform));
    param->setColor1(color);
    draw(m_colorFillRectObject);
}
void Renderer::drawCircle(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
{
    auto param = m_colorDrawCircleObject->getContext()->getParameter();
    glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0)),
        glm::vec3(size / 2.f, 1));
    param->setTransform(m_orthoMat * (getModelMatrix() * transform));
    param->setColor1(color);
    draw(m_colorDrawCircleObject);
}
void Renderer::fillCircle(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
{
    auto param = m_colorFillCircleObject->getContext()->getParameter();
    glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0)),
        glm::vec3(size / 2.f, 1));
    param->setTransform(m_orthoMat * (getModelMatrix() * transform));
    param->setColor1(color);
    draw(m_colorFillCircleObject);
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
    param->setTransform(m_orthoMat * (getModelMatrix() * transform));
    param->setTexture(sprite->texture);
    param->setColor1(color);
    draw(m_stringObject);
}

void Renderer::drawString(const glm::vec2& pos, int fontSize, const std::u16string& str, const glm::vec4& color)
{
    drawString(pos, fontSize, str, color, 0);
}
void Renderer::drawString(const glm::vec2& pos, int fontSize, const std::u16string& str, const glm::vec4& color, int baseHeight)
{
    if (!m_fontMap) {
        return;
    }
    auto sprites = m_fontMap->load(fontSize, str);
    // get char height of baseline.
    float maxY = -1.f;
    for (auto sprite : sprites) {
        if (maxY < sprite->metrics.size.y) {
            maxY = sprite->metrics.size.y;
        }
    }
    glm::vec2 offset = pos;
    for (auto sprite : sprites) {
        float xpos = offset.x + sprite->metrics.bearing.x;
        float ypos = offset.y - sprite->metrics.bearing.y;
        ypos += baseHeight > 0 ? baseHeight : maxY;
        // draw
        auto param = m_stringObject->getContext()->getParameter();
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, 0));
        glm::mat4 transform = glm::scale(translate, glm::vec3(sprite->metrics.size, 1));
        param->setTransform(m_orthoMat * (getModelMatrix() * transform));
        param->setTexture(sprite->texture);
        param->setColor1(color);
        draw(m_stringObject);
        // move to next char.
        offset.x += sprite->metrics.advance.x >> 6;
    }
}
glm::vec2 Renderer::measureString(int fontSize, const std::u16string& str)
{
    if (!m_fontMap) {
        return glm::vec2 { 0, 0 };
    }
    return m_fontMap->measureString(fontSize, str);
}
// matrix
void Renderer::pushMatrix() { m_stack.emplace_back(MatrixStack()); }
void Renderer::translate(const glm::vec3& pos) { m_stack.back().push(glm::translate(glm::mat4(1.0f), pos)); }
void Renderer::rotateX(float a) { m_stack.back().push(glm::rotate(glm::mat4(1.0f), a, glm::vec3(1, 0, 0))); }
void Renderer::rotateY(float a) { m_stack.back().push(glm::rotate(glm::mat4(1.0f), a, glm::vec3(0, 1, 0))); }
void Renderer::rotateZ(float a) { m_stack.back().push(glm::rotate(glm::mat4(1.0f), a, glm::vec3(0, 0, 1))); }
void Renderer::scale(const glm::vec3& scale) { m_stack.back().push(glm::scale(glm::mat4(1.0f), scale)); }
glm::mat4 Renderer::getModelMatrix() const
{
    glm::mat4 m(1.0f);
    auto iter = m_stack.rbegin();
    while (iter != m_stack.rend()) {
        auto i = (*iter).mult();
        m = m * i;
        ++iter;
    }
    return m;
}
void Renderer::popMatrix() { m_stack.pop_back(); }
// property
void Renderer::setFontMap(const std::shared_ptr<FontMap>& fontMap) { m_fontMap = fontMap; }
std::shared_ptr<FontMap> Renderer::getFontMap() const { return m_fontMap; }
// private
void Renderer::draw(const RenderingObject::Instance& obj)
{
    obj->draw();
}
}