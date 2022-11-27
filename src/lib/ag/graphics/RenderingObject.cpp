#include <ag/Engine.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/IShaderCompiler.hpp>
#include <ag/graphics/RenderingContext.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/graphics/ShaderCode.hpp>
#include <ag/native/glm.hpp>

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
std::shared_ptr<RenderingObject> RenderingObject::createColorRectangle(bool isFill)
{
    auto compiler = Engine::getInstance()->getGraphicsDriver()->getShaderCompiler();
    const float left = 0;
    const float right = 1;
    const float top = 0;
    const float bottom = 1;
    auto context = createRenderingContext();
    auto shader = compiler->compileFromPartedSource(ag::internal::GL_ColorVertexShader, ag::internal::GL_ColorFragmentShader);
    if (isFill) {
        const std::vector<glm::vec2> verts { { left, top }, { right, top }, { right, bottom }, { left, bottom } };
        const std::vector<unsigned short> index { 0, 1, 2, 2, 3, 0 };
        context->updateVertex(verts);
        context->updateIndex(index);
        return std::make_shared<RenderingObject>(PrimitiveType::Triangles, 0, shader, context);
    } else {
        const std::vector<glm::vec2> verts {
            { left, top },
            { left, bottom },
            { right, bottom },
            { right, top },
            { left, top },
        };
        context->updateVertex(verts);
        return std::make_shared<RenderingObject>(PrimitiveType::LineStrip, 5, shader, context);
    }
}
std::shared_ptr<RenderingObject> RenderingObject::createColorCircle(bool isFill)
{
    auto compiler = Engine::getInstance()->getGraphicsDriver()->getShaderCompiler();
    auto context = createRenderingContext();
    std::vector<glm::vec2> verts;
    float degree = 0.0f;
    float applyScale = isFill ? 1.0f : 1.0f; //m_scaleUniform->value;
    float half = applyScale;
    int points = 0;
    float fx = 0.0f;
    float fy = 0.0f;
    while (degree < 360.0f) {
        degree += 360.0f / static_cast<float>(100 /* split count */);
        float radian = degree * (3.14f / 180.0f);
        float x = std::cosf(radian);
        float y = std::sinf(radian);
        if (fx <= 0.0f || fy <= 0.0f) {
            fx = x;
            fy = y;
        }
        verts.push_back({ half + (x * applyScale), half + (y * applyScale) });
        points++;
    }
    verts.push_back({ half + (fx * applyScale), half + (fy * applyScale) });
    points++;
    context->updateVertex(verts);
    //context->updateIndex(index);
    auto shader = compiler->compileFromPartedSource(ag::internal::GL_ColorVertexShader, ag::internal::GL_ColorFragmentShader);
    return std::make_shared<RenderingObject>(isFill ? PrimitiveType::Polygon : PrimitiveType::LineStrip, points, shader, context);
}
// property
PrimitiveType RenderingObject::getPrimitiveType() const { return m_primitiveType; }
int RenderingObject::getPrimitiveCount() const { return m_primitiveCount; }
std::shared_ptr<IShader> RenderingObject::getShader() const { return m_shader; }
std::shared_ptr<RenderingContext> RenderingObject::getContext() const { return m_context; }
// private

RenderingContext::Instance RenderingObject::createRenderingContext()
{
#if AG_OPEN_GL
    return std::make_shared<OglRenderingContext>();
#elif AG_METAL
    return std::make_shared<MtlRenderingContext>();
#else
    return nullptr;
#endif
}
}