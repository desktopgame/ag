#include <ag/graphics/RenderingContext.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/graphics/ogl/OglBuffer.hpp>
#include <ag/graphics/ogl/OglRenderFunction.hpp>
#include <ag/graphics/ogl/OglShader.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
void OglRenderFunction::draw(const std::shared_ptr<RenderingObject>& object)
{
    auto context = object->getContext();
    auto shader = object->getShader();
    GLenum primType = convPrimitiveType(object->getPrimitiveType());
    size_t indexLen = context->getIndexLength();
    context->setup(shader);
    if (indexLen > 0) {
        glDrawElements(primType, indexLen, GL_UNSIGNED_SHORT, nullptr);
    } else {
        glDrawArrays(primType, 0, object->getPrimitiveCount());
    }
    context->teardown(shader);
}
// private
GLenum OglRenderFunction::convPrimitiveType(PrimitiveType type)
{
    switch (type) {
    case PrimitiveType::Polygon:
        return GL_POLYGON;
    case PrimitiveType::Triangles:
        return GL_TRIANGLES;
    case PrimitiveType::LineStrip:
        return GL_LINE_STRIP;
    }
    return GL_TRIANGLES;
}
}