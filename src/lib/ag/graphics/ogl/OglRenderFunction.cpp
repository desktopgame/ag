#ifdef AG_OPEN_GL
#include <ag/Window.hpp>
#include <ag/graphics/RenderingContext.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/graphics/ogl/OglBuffer.hpp>
#include <ag/graphics/ogl/OglRenderFunction.hpp>
#include <ag/graphics/ogl/OglShader.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
void OglRenderFunction::begin(const std::shared_ptr<Window>& window, const RenderPass& pass)
{
    glm::vec3 clearColor = window->getClearColor();
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}
void OglRenderFunction::end()
{
}
// private
}
#endif