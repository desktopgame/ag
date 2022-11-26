#include <ag/Engine.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/IRenderFunction.hpp>
#include <ag/graphics/Renderer.hpp>

namespace ag {
Renderer::Renderer()
    : m_projMat()
    // , m_color()
    , m_colorRectObject(RenderingObject::createColorRectangle())
    , m_colorCircleObject(RenderingObject::createColorCircle(true))
{
}

void Renderer::resize(int width, int height)
{
    float fWidth = static_cast<float>(width);
    float fHeight = static_cast<float>(height);
    m_projMat = glm::ortho(0.0f, fWidth, fHeight, 0.0f /* lrbt*/, 0.0f, 1.0f);
}
void Renderer::resize(const glm::ivec2& size)
{
    resize(size.x, size.y);
}
void Renderer::drawRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
{
    auto param = m_colorRectObject->getContext()->getParameter();
    glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0)),
        glm::vec3(size, 1));
    param->setTransform(m_projMat * transform);
    param->setColor1(color);
    ag::Engine::getInstance()->getGraphicsDriver()->getRenderFunction()->draw(m_colorRectObject);
}
void Renderer::drawCircle(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
{
    auto param = m_colorCircleObject->getContext()->getParameter();
    glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0)),
        glm::vec3(size / 2.f, 1));
    param->setTransform(m_projMat * transform);
    param->setColor1(color);
    ag::Engine::getInstance()->getGraphicsDriver()->getRenderFunction()->draw(m_colorCircleObject);
}
}