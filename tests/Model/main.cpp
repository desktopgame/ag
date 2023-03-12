#include <ag/agOne.hpp>
#include <ag/easy/App.hpp>
#include <ag/graphics/Model.hpp>
#include <ag/native/glm.hpp>
#include <cassert>

class MyApp : public ag::easy::App {
public:
    MyApp(int argc, char* argv[])
        : App(argc, argv)
    {
    }
    void start(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
        m_rect = ag::RenderingObject::createColorRectangle(true);
        if (ag::isBuiltOnOpenGL()) {
            m_shader = ag::Engine::getInstance()->getGraphicsDriver()->getShaderCompiler()->compileFromPartedSource(ag::internal::GL_ModelColorNoLightVertexShader, ag::internal::GL_ModelColorNoLightFragmentShader);
        } else if (ag::isBuiltOnMetal()) {
            m_shader = ag::Engine::getInstance()->getGraphicsDriver()->getShaderCompiler()->compileFromSingleSource(ag::internal::Metal_ModelColorNoLightVFShader);
        } else if (ag::isBuiltOnDirectX()) {
            m_shader = ag::Engine::getInstance()->getGraphicsDriver()->getShaderCompiler()->compileFromPartedSource(ag::internal::DX_ModelColorNoLightVertexShader, ag::internal::DX_ModelColorNoLightFragmentShader);
        }
        m_model = ag::Model::loadFromFile("testdata/models/Cube.fbx");
        m_camera.resize(1280, 720);
        m_camera.lookAt(glm::vec3(0, 4, -4), glm::vec3(0, 0, 0), glm::vec3(0, -1, 0));
        m_angle = 0.0f;
    }

    void update(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
        auto engine = ag::Engine::getInstance();
        auto looper = engine->getLooper();
        // 3D rendering
        engine->getGraphicsDriver()->getRenderFunction()->begin(w, ag::RenderPass::default3D());
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, glm::radians(m_angle += (100.0f * looper->deltaTime())), glm::vec3(0, 1, 0));
        transform = glm::scale(transform, glm::vec3(0.01f, 0.01f, 0.01f));
        m_model->getRootNode()->draw(m_shader, m_camera, transform);
        engine->getGraphicsDriver()->getRenderFunction()->end();
        // 2D rendering
        engine->getGraphicsDriver()->getRenderFunction()->begin(w, ag::RenderPass::default2D());
        {
            glm::vec2 pos = glm::vec2(0, 0);
            glm::vec2 size = glm::vec2(100, 100);
            glm::mat4 m_projMat = glm::ortho(0.0f, 1280.f, 720.f, 0.0f, -1.0f, 1.0f);
            glm::vec4 color = glm::vec4(1, 0, 0, 1);
            auto param = m_rect->getContext()->getParameter();
            glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0)),
                glm::vec3(size, 1));
            param->setTransform(m_projMat * transform);
            param->setColor(color);
            m_rect->draw();
        }
        engine->getGraphicsDriver()->getRenderFunction()->end();
    }

private:
    ag::IShader::Instance m_shader;
    ag::RenderingObject::Instance m_rect;
    ag::Model::Instance m_model;
    ag::Camera m_camera;
    float m_angle;
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(1280, 720, false, "Model");
}