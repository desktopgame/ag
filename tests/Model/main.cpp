#include <ag/agOne.hpp>
#include <ag/graphics/Model.hpp>
#include <ag/native/glm.hpp>
#include <cassert>

int main(int argc, char* argv[])
{
    auto engine = ag::Engine::getInstance()->startup(argc, argv);
    auto looper = engine->getLooper();
    auto window = ag::Window::create(1280, 720, false, "Model");
    window->makeContextCurrent();
    // create rectangle.
    //ag::IShader::Instance shader = ag::Engine::getInstance()->getGraphicsDriver()->getShaderCompiler()->compileFromPartedSource(ag::internal::GL_ModelVertexShader, ag::internal::GL_ModelFragmentShader);
    ag::IShader::Instance shader = ag::Engine::getInstance()->getGraphicsDriver()->getShaderCompiler()->compileFromSingleSource(ag::internal::Metal_ModelVFShader);
    ag::Model::Instance model = ag::Model::loadFromFile("testdata/models/IronMan.obj");
    // start main loop.
    float angle = 0.0f;
    while (looper->nextLoop()) {
        while (looper->nextWindow()) {
            auto window = looper->acquire();
            engine->getGraphicsDriver()->getRenderFunction()->begin(window, ag::RenderPass {});
            glm::mat4 proj = glm::perspective(30.f, 1280.0f / 720.0f, 1.f, 1000.f);
            glm::mat4 view = glm::lookAt(glm::vec3(0, 2, -4), glm::vec3(0, 0, 0), glm::vec3(0, -1, 0));
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::rotate(transform, glm::radians(angle += (100.0f * looper->deltaTime())), glm::vec3(0, 1, 0));
            transform = glm::scale(transform, glm::vec3(0.01f, 0.01f, 0.01f));
            model->getRootNode()->draw(shader, proj * view * transform);
            engine->getGraphicsDriver()->getRenderFunction()->end();
            looper->release();
        }
    }
    return 0;
}