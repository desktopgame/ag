#include <ag/Engine.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/IShaderCompiler.hpp>
#include <ag/graphics/RenderingContext.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/graphics/ShaderCode.hpp>
#include <ag/native/glm.hpp>

#ifdef AG_DEBUG
#include <ag/graphics/ogl/OglRenderingContext.hpp>
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
std::shared_ptr<RenderingObject> RenderingObject::createColorRectangle()
{
    auto compiler = Engine::getInstance()->getGraphicsDriver()->getShaderCompiler();
    const float left = 0;
    const float right = 1;
    const float top = 0;
    const float bottom = 1;
    const std::vector<glm::vec2> verts { { left, top }, { right, top }, { right, bottom }, { left, bottom } };
    const std::vector<unsigned short> index { 0, 1, 2, 2, 3, 0 };
    auto context = createRenderingContext();
    context->updateVertex(verts);
    context->updateIndex(index);
    auto shader = compiler->compileFromSource(ag::internal::GL_ColorVertexShader, ag::internal::GL_ColorFragmentShader);
    return std::make_shared<RenderingObject>(PrimitiveType::Triangles, 0, shader, context);
}
// property
PrimitiveType RenderingObject::getPrimitiveType() const { return m_primitiveType; }
int RenderingObject::getPrimitiveCount() const { return m_primitiveCount; }
std::shared_ptr<IShader> RenderingObject::getShader() const { return m_shader; }
std::shared_ptr<RenderingContext> RenderingObject::getContext() const { return m_context; }
// private

RenderingContext::Instance RenderingObject::createRenderingContext()
{
#ifdef AG_DEBUG
    return std::make_shared<OglRenderingContext>();
#else
    return nullptr;
#endif
}
}