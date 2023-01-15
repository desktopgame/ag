#include <ag/Engine.hpp>
#include <ag/graphics/IGraphicsDevice.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/IShaderCompiler.hpp>
#include <ag/graphics/RenderingContext.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/graphics/ShaderCode.hpp>
#include <ag/graphics/VertexData2D.hpp>
#include <ag/native/glm.hpp>
#include <cmath>

#ifdef AG_OPEN_GL
#include <ag/graphics/ogl/OglRenderingContext.hpp>
#endif

#ifdef AG_METAL
#include <ag/graphics/mtl/MtlRenderingContext.hpp>
#endif

namespace ag {

RenderingObject::RenderingObject(
    PrimitiveType primitiveType,
    int primitiveCount,
    const std::shared_ptr<IShader>& shader,
    const std::shared_ptr<RenderingContext>& context)
    : m_primitiveType(primitiveType)
    , m_primitiveCount(primitiveCount)
    , m_shader(shader)
    , m_context(context)
{
}
// factory
std::shared_ptr<RenderingObject> RenderingObject::createString()
{
    auto compiler = Engine::getInstance()->getGraphicsDriver()->getShaderCompiler();
#if AG_OPEN_GL
    auto shader = compiler->compileFromPartedSource(ag::internal::GL_StringVertexShader, ag::internal::GL_StringFragmentShader);
#elif AG_METAL
    auto shader = compiler->compileFromSingleSource(ag::internal::Metal_StringVFShader);
#else
    std::shared_ptr<IShader> shader = nullptr;
#endif
    return createTextureRectangle(shader);
}
std::shared_ptr<RenderingObject> RenderingObject::createTextureRectangle()
{
    auto compiler = Engine::getInstance()->getGraphicsDriver()->getShaderCompiler();
#if AG_OPEN_GL
    auto shader = compiler->compileFromPartedSource(ag::internal::GL_TextureVertexShader, ag::internal::GL_TextureFragmentShader);
#elif AG_METAL
    auto shader = compiler->compileFromSingleSource(ag::internal::Metal_TextureVFShader);
#else
    std::shared_ptr<IShader> shader = nullptr;
#endif
    return createTextureRectangle(shader);
}
std::shared_ptr<RenderingObject> RenderingObject::createColorRectangle(bool isFill)
{
    auto compiler = Engine::getInstance()->getGraphicsDriver()->getShaderCompiler();
    const float left = 0;
    const float right = 1;
    const float top = 0;
    const float bottom = 1;
    auto context = createRenderingContext();
#if AG_OPEN_GL
    auto shader = compiler->compileFromPartedSource(ag::internal::GL_ColorVertexShader, ag::internal::GL_ColorFragmentShader);
#elif AG_METAL
    auto shader = compiler->compileFromSingleSource(ag::internal::Metal_ColorVFShader);
#else
    std::shared_ptr<IShader> shader = nullptr;
#endif
    if (isFill) {
        const std::vector<glm::vec2> verts { { left, top }, { right, top }, { right, bottom }, { left, bottom } };

#if AG_OPEN_GL
        const std::vector<unsigned int> index { 1, 0, 3, 1, 3, 2 };
#elif AG_METAL || AG_DIRECT_X
        const std::vector<unsigned int> index { 1, 2, 3, 0, 1, 3 };
#else
        std::shared_ptr<IShader> shader = nullptr;
#endif
        context->updateVertex(verts.data(), static_cast<int>(verts.size()));
        context->updateIndex(index.data(), static_cast<int>(index.size()));
        return std::make_shared<RenderingObject>(PrimitiveType::Triangles, 0, shader, context);
    } else {
        const std::vector<glm::vec2> verts {
            { left, top },
            { left, bottom },
            { right, bottom },
            { right, top },
            { left, top },
        };
        context->updateVertex(verts.data(), static_cast<int>(verts.size()));
        return std::make_shared<RenderingObject>(PrimitiveType::LineStrip, 5, shader, context);
    }
}
std::shared_ptr<RenderingObject> RenderingObject::createColorCircle(bool isFill)
{
    auto compiler = Engine::getInstance()->getGraphicsDriver()->getShaderCompiler();
    auto context = createRenderingContext();
    std::vector<glm::vec2> verts;
#if AG_OPEN_GL
    float degree = 0.0f;
#elif AG_METAL || AG_DIRECT_X
    float degree = 360.0f;
#endif
    float applyScale = 1.0f;
    float half = applyScale;
    int points = 0;
    float fx = 0.0f;
    float fy = 0.0f;
    glm::vec2 atlast;
    // first point
    verts.push_back({ half + ::cosf(0.f), half + ::sinf(0.f) });
    points++;
    // connect points
#if AG_OPEN_GL
    while (degree < 360.0f) {
#elif AG_METAL || AG_DIRECT_X
    while (degree > 0.0f) {
#endif
#if AG_OPEN_GL
        degree += 360.0f / static_cast<float>(100 /* split count */);
#elif AG_METAL || AG_DIRECT_X
        degree -= 360.0f / static_cast<float>(100 /* split count */);
#endif
        float radian = degree * (3.14f / 180.0f);
        float x = ::cosf(radian);
        float y = ::sinf(radian);
        if (fx <= 0.0f || fy <= 0.0f) {
            fx = x;
            fy = y;
        }
        if (isFill && points >= 2) {
            verts.push_back(atlast);
            points++;
        }
        atlast = { half + (x * applyScale), half + (y * applyScale) };
        verts.push_back(atlast);
        points++;
        // put a center point
        if (isFill && points % 2 == 0) {
            glm::vec2 sec = verts.back();
            verts.pop_back();
            glm::vec2 one = verts.back();
            verts.pop_back();
            verts.push_back(sec);
            verts.push_back(one);
            verts.push_back({ half, half });
        }
    }
    context->updateVertex(verts.data(), static_cast<int>(verts.size()));
#if AG_OPEN_GL
    auto shader = compiler->compileFromPartedSource(ag::internal::GL_ColorVertexShader, ag::internal::GL_ColorFragmentShader);
#elif AG_METAL
    auto shader = compiler->compileFromSingleSource(ag::internal::Metal_ColorVFShader);
#else
std::shared_ptr<IShader> shader = nullptr;
#endif
    return std::make_shared<RenderingObject>(isFill ? PrimitiveType::Triangles : PrimitiveType::LineStrip, verts.size(), shader, context);
}
// draw
void RenderingObject::draw()
{
    m_context->draw(m_shader, m_primitiveType, m_primitiveCount);
}
// property
PrimitiveType RenderingObject::getPrimitiveType() const { return m_primitiveType; }
int RenderingObject::getPrimitiveCount() const { return m_primitiveCount; }
std::shared_ptr<IShader> RenderingObject::getShader() const { return m_shader; }
std::shared_ptr<RenderingContext> RenderingObject::getContext() const { return m_context; }
// private
std::shared_ptr<RenderingObject> RenderingObject::createTextureRectangle(const std::shared_ptr<IShader>& shader)
{
    const float left = 0;
    const float right = 1;
    const float top = 0;
    const float bottom = 1;
    auto context = createRenderingContext();
    const std::vector<VertexData2D> verts {
        { { left, top },
            { 0, 0 } },
        { { right, top },
            { 1, 0 } },
        { { right, bottom },
            { 1, 1 } },
        { { left, bottom },
            { 0, 1 } }
    };
#if AG_OPEN_GL
    const std::vector<unsigned int> index { 1, 0, 3, 1, 3, 2 };
#elif AG_METAL || AG_DIRECT_X
    const std::vector<unsigned int> index { 1, 2, 3, 0, 1, 3 };
#endif
    context->updateVertex(verts.data(), static_cast<int>(verts.size()));
    context->updateIndex(index.data(), static_cast<int>(index.size()));
    return std::make_shared<RenderingObject>(PrimitiveType::Triangles, 0, shader, context);
}
RenderingContext::Instance RenderingObject::createRenderingContext()
{
    return ag::Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice()->newRenderingContext();
}
}
