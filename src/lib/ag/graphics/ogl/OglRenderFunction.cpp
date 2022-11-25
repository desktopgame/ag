#include <ag/graphics/RenderingContext.hpp>
#include <ag/graphics/ogl/OglBuffer.hpp>
#include <ag/graphics/ogl/OglRenderFunction.hpp>
#include <ag/graphics/ogl/OglShader.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
void OglRenderFunction::draw(const std::shared_ptr<IShader>& shader, const std::shared_ptr<RenderingContext>& context)
{
    context->setup(shader);
    glDrawElements(GL_TRIANGLES, context->getIndexLength(), GL_UNSIGNED_SHORT, nullptr);
    context->teardown(shader);
}
}