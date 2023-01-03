#include <ag/agOne.hpp>
#include <ag/graphics/Model.hpp>
#include <ag/native/glm.hpp>
#include <cassert>

int main(int argc, char* argv[])
{
    auto engine = ag::Engine::getInstance()->startup(argc, argv);
    auto looper = engine->getLooper();
    auto window = ag::Window::create(1280, 720, false, "LowLevel");
    window->makeContextCurrent();
    // create rectangle.
    //ag::IShader::Instance shader = ag::Engine::getInstance()->getGraphicsDriver()->getShaderCompiler()->compileFromPartedSource(ag::internal::GL_ModelVertexShader, ag::internal::GL_ModelFragmentShader);
    ag::IShader::Instance shader = ag::Engine::getInstance()->getGraphicsDriver()->getShaderCompiler()->compileFromSingleSource(ag::internal::Metal_ModelVFShader);
    ag::Model::Instance model = ag::Model::loadFromFile("testdata/models/Cube.fbx");
    // start main loop.
    float angle = 0.0f;
    while (looper->nextLoop()) {
        while (looper->nextWindow()) {
            auto window = looper->acquire();
            glm::mat4 proj = glm::perspective(30.f, 1280.0f / 720.0f, 1.f, 1000.f);
            glm::mat4 view = glm::lookAt(glm::vec3(0, 0, -2), glm::vec3(0, 0, 0), glm::vec3(0, -1, 0));
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::rotate(transform, glm::radians(angle += 2.0f), glm::vec3(0, 1, 0));
            transform = glm::scale(transform, glm::vec3(0.001f, 0.001f, 0.001f));
            model->getRootNode()->draw(shader, proj * view * transform);
            looper->release();
        }
    }
    return 0;
}