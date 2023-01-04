#include <ag/agOne.hpp>
#include <ag/native/glm.hpp>
#include <cassert>

int main(int argc, char* argv[])
{
    auto engine = ag::Engine::getInstance()->startup(argc, argv);
    auto looper = engine->getLooper();
    auto window = ag::Window::create(1280, 720, false, "LowLevel");
    window->makeContextCurrent();
    // create rectangle.
    ag::RenderingObject::Instance rect = ag::RenderingObject::createColorRectangle(true);
    // start main loop.
    while (looper->nextLoop()) {
        while (looper->nextWindow()) {
            auto window = looper->acquire();
            engine->getGraphicsDriver()->getRenderFunction()->begin(window, ag::RenderPass {});
            glm::vec2 pos = glm::vec2(0, 0);
            glm::vec2 size = glm::vec2(100, 100);
            glm::mat4 m_projMat = glm::ortho(0.0f, 1280.f, 720.f, 0.0f /* lrbt*/, -1.0f, 1.0f);
            glm::vec4 color = glm::vec4(1, 0, 0, 1);
            auto param = rect->getContext()->getParameter();
            glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0)),
                glm::vec3(size, 1));
            param->setTransform(m_projMat * transform);
            param->setColor(color);
            rect->draw();
            engine->getGraphicsDriver()->getRenderFunction()->end();
            looper->release();
        }
    }
    return 0;
}