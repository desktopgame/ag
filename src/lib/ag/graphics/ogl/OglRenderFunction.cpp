#ifdef AG_OPEN_GL
#include <ag/Window.hpp>
#include <ag/graphics/RenderPass.hpp>
#include <ag/graphics/RenderingContext.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/graphics/ogl/OglBuffer.hpp>
#include <ag/graphics/ogl/OglRenderFunction.hpp>
#include <ag/graphics/ogl/OglShader.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
void OglRenderFunction::link(const std::shared_ptr<Window>& window) { }
void OglRenderFunction::begin(const std::shared_ptr<Window>& window, const RenderPass& pass)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    if (pass.renderMode == RenderMode::Render2D) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_DEPTH_TEST);
    } else if (pass.renderMode == RenderMode::Render3D) {
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
    }
}
void OglRenderFunction::end()
{
}
void OglRenderFunction::clear(const std::shared_ptr<Window>& window)
{
    glm::vec3 clearColor = window->getClearColor();
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void OglRenderFunction::present(const std::shared_ptr<Window>& window)
{
}
// private
}
#endif