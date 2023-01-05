#include <ag/agOne.hpp>
#include <ag/graphics/Model.hpp>
#include <ag/native/glm.hpp>
#include <cassert>

int main(int argc, char* argv[])
{
    auto engine = ag::Engine::getInstance()->startup(argc, argv);
    auto looper = engine->getLooper();
    auto window = ag::Window::create(1280, 720, false, "TextureModel");
    window->makeContextCurrent();
    // create rectangle.
    ag::IShader::Instance shader;
    ag::RenderingObject::Instance rect = ag::RenderingObject::createColorRectangle(true);
    if (ag::isBuiltOnOpenGL()) {
        shader = ag::Engine::getInstance()->getGraphicsDriver()->getShaderCompiler()->compileFromPartedSource(ag::internal::GL_ModelTextureNoLightVertexShader, ag::internal::GL_ModelTextureNoLightFragmentShader);
    } else if (ag::isBuiltOnMetal()) {
        shader = ag::Engine::getInstance()->getGraphicsDriver()->getShaderCompiler()->compileFromSingleSource(ag::internal::Metal_ModelTextureNoLightVFShader);
    }
    ag::Model::Instance model = ag::Model::loadFromFile("testdata/models/TextureCube.fbx");
    // start main loop.
    ag::Camera cam;
    cam.resize(1280, 720);
    cam.lookAt(glm::vec3(0, 4, -4), glm::vec3(0, 0, 0), glm::vec3(0, -1, 0));
    float angle = 0.0f;
    while (looper->nextLoop()) {
        while (looper->nextWindow()) {
            auto window = looper->acquire();
            // 3D rendering
            engine->getGraphicsDriver()->getRenderFunction()->begin(window, ag::RenderPass::default3D());
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::rotate(transform, glm::radians(angle += (100.0f * looper->deltaTime())), glm::vec3(0, 1, 0));
            transform = glm::scale(transform, glm::vec3(0.01f, 0.01f, 0.01f));
            model->getRootNode()->draw(shader, cam, transform);
            engine->getGraphicsDriver()->getRenderFunction()->end();
            // 2D rendering
            engine->getGraphicsDriver()->getRenderFunction()->begin(window, ag::RenderPass::default2D());
            {
                glm::vec2 pos = glm::vec2(0, 0);
                glm::vec2 size = glm::vec2(100, 100);
                glm::mat4 m_projMat = glm::ortho(0.0f, 1280.f, 720.f, 0.0f, -1.0f, 1.0f);
                glm::vec4 color = glm::vec4(1, 0, 0, 1);
                auto param = rect->getContext()->getParameter();
                glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0)),
                    glm::vec3(size, 1));
                param->setTransform(m_projMat * transform);
                param->setColor(color);
                rect->draw();
            }
            engine->getGraphicsDriver()->getRenderFunction()->end();
            looper->release();
        }
    }
    return 0;
}