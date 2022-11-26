#include <ag/Engine.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/IRenderFunction.hpp>
#include <ag/graphics/IShaderCompiler.hpp>
#include <ag/graphics/Renderer.hpp>
#include <ag/graphics/ShaderCode.hpp>

#ifdef AG_DEBUG
#include <ag/graphics/ogl/OglRenderingContext.hpp>
#endif

namespace ag {
Renderer::Renderer()
    : m_projMat()
    // , m_color()
    , m_colorRectShader()
    , m_colorRectCtx()
{

    auto compiler = ag::Engine::getInstance()->getGraphicsDriver()->getShaderCompiler();
    // Rect
    const float left = 0;
    const float right = 1;
    const float top = 0;
    const float bottom = 1;
    const std::vector<glm::vec2> verts { { left, top }, { right, top }, { right, bottom }, { left, bottom } };
    const std::vector<unsigned short> index { 0, 1, 2, 2, 3, 0 };
    m_colorRectCtx = createRenderingContext();
    m_colorRectCtx->updateVertex(verts);
    m_colorRectCtx->updateIndex(index);
    m_colorRectShader = compiler->compileFromSource(ag::internal::GL_ColorVertexShader, ag::internal::GL_ColorFragmentShader);
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
    auto param = m_colorRectCtx->getParameter();
    glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0)),
        glm::vec3(size, 1));
    param->setTransform(m_projMat * transform);
    param->setColor1(color);
    ag::Engine::getInstance()->getGraphicsDriver()->getRenderFunction()->draw(m_colorRectShader, m_colorRectCtx);
}
// private
RenderingContext::Instance Renderer::createRenderingContext()
{
#ifdef AG_DEBUG
    return std::make_shared<OglRenderingContext>();
#else
    return nullptr;
#endif
}
}