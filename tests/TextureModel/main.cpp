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
        m_model = ag::Model::loadFromFile("testdata/models/TextureCube.fbx");
        m_angle = 0.0f;
    }

    void update(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
        auto engine = ag::Engine::getInstance();
        auto looper = engine->getLooper();
        // 3D rendering
        r->begin(w, ag::RenderPass::default3D());
        r->lookAt(glm::vec3(0, 4, -4), glm::vec3(0, 0, 0), glm::vec3(0, -1, 0));
        r->pushMatrix();
        r->rotateY(glm::radians(m_angle += (100.0f * looper->deltaTime())));
        r->scale(glm::vec3(0.01f, 0.01f, 0.01f));
        r->drawModel(glm::vec3(), m_model, ag::MeshDrawMode::TextureNoLight);
        r->popMatrix();
        r->end();
        // 2D rendering
        r->begin(w, ag::RenderPass::default2D());
        r->fillRect(glm::vec2(), glm::vec2(100, 100), glm::vec4(1, 0, 0, 1));
        r->end();
    }

private:
    ag::Model::Instance m_model;
    float m_angle;
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(1280, 720, false, "TextureModel");
}