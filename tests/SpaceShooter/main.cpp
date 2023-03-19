#include <ag/agOne.hpp>
#include <ag/easy/App.hpp>
#include <ag/graphics/Model.hpp>
#include <ag/native/glm.hpp>
#include <cassert>

class MyApp : public ag::easy::App {
public:
    MyApp(int argc, char* argv[])
        : App(argc, argv)
        , m_playerPosition(0, 0, 10)
    {
    }
    void start(const ag::Window::Instance& window, const ag::InputState& input, const ag::Renderer::Instance& renderer)
    {
        m_angle = 0.0f;
    }

    void update(const ag::Window::Instance& window, const ag::InputState& input, const ag::Renderer::Instance& renderer)
    {
        auto engine = ag::Engine::getInstance();
        auto looper = engine->getLooper();
        // 3D rendering
        renderer->begin(window, ag::RenderPass::default3D());
        renderer->lookAt(m_playerPosition, m_playerPosition + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
        m_angle += (100.0f * looper->deltaTime());
        if (input.getKeyboardState().getKeyState(ag::KeyCode::left) == ag::ButtonState::Held) {
            m_playerPosition.x -= 10.0f * looper->deltaTime();
        } else if (input.getKeyboardState().getKeyState(ag::KeyCode::right) == ag::ButtonState::Held) {
            m_playerPosition.x += 10.0f * looper->deltaTime();
        }
        m_playerPosition.z -= looper->deltaTime();

        renderer->pushMatrix();
        renderer->translate(glm::vec3(-2.0f, 0, 0));
        renderer->rotateY(glm::radians(m_angle));
        renderer->scale(glm::vec3(0.01f, 0.01f, 0.01f));
        renderer->drawModel(glm::vec3(0, 0, 0), loadModel("testdata/models/Cube.fbx"), ag::MeshDrawMode::ColorNoLight);
        renderer->popMatrix();

        renderer->pushMatrix();
        renderer->translate(glm::vec3(2.0f, 0, 0));
        renderer->rotateY(glm::radians(m_angle));
        renderer->scale(glm::vec3(0.01f, 0.01f, 0.01f));
        renderer->drawModel(glm::vec3(0, 0, 0), loadModel("testdata/models/TextureCube.fbx"), ag::MeshDrawMode::TextureNoLight);
        renderer->popMatrix();

        renderer->end();
        // 2D rendering
        renderer->begin(window, ag::RenderPass::default2D());
        renderer->fillRect(glm::vec2(), glm::vec2(100, 100), glm::vec4(1, 0, 0, 1));
        renderer->end();
    }

private:
    glm::vec3 m_playerPosition;
    float m_angle;
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(1280, 720, false, "ModelDraw");
}