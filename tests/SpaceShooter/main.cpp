#include "Bullet.hpp"
#include <ag/agOne.hpp>
#include <ag/easy/App.hpp>
#include <ag/graphics/Model.hpp>
#include <ag/native/glm.hpp>
#include <ag/object/ModelRenderer.hpp>
#include <ag/util/Random.hpp>
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
        m_speed = 1.0f;
        for (int i = 0; i < 10; i++) {
            m_objects.emplace_back(createDebri());
        }
    }

    void update(const ag::Window::Instance& window, const ag::InputState& input, const ag::Renderer::Instance& renderer)
    {
        auto engine = ag::Engine::getInstance();
        auto looper = engine->getLooper();
        // 3D rendering
        renderer->begin(window, ag::RenderPass::default3D());
        renderer->lookAt(m_playerPosition, m_playerPosition + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
        m_angle += (100.0f * looper->deltaTime());
        m_speed = 1.0f;
        if (input.getKeyboardState().getKeyState(ag::KeyCode::left) == ag::ButtonState::Held) {
            m_playerPosition.x -= 10.0f * looper->deltaTime();
        } else if (input.getKeyboardState().getKeyState(ag::KeyCode::right) == ag::ButtonState::Held) {
            m_playerPosition.x += 10.0f * looper->deltaTime();
        } else if (input.getKeyboardState().getKeyState(ag::KeyCode::up) == ag::ButtonState::Held) {
            m_speed = 3.0f;
        } else if (input.getKeyboardState().getKeyState(ag::KeyCode::z) == ag::ButtonState::Held) {
            m_objects.push_back(createBullet());
        }
        m_playerPosition.z -= m_speed * looper->deltaTime();

        for (auto obj : m_objects) {
            obj->update(input, looper->deltaTime());
        }
        for (auto obj : m_objects) {
            obj->draw(renderer);
        }
        int size = m_objects.size();
        auto iter = std::remove_if(m_objects.begin(), m_objects.end(), [&](ag::GameObject::Instance e) -> bool {
            return e->getPosition().z - m_playerPosition.z > 3.0f;
        });
        m_objects.erase(iter, m_objects.end());
        while (m_objects.size() < size) {
            m_objects.emplace_back(createDebri());
        }

        renderer->end();
        // 2D rendering
        renderer->begin(window, ag::RenderPass::default2D());
        renderer->drawTexture((glm::vec2(1280, 720) - glm::vec2(120, 120)) / 2.0f, loadTexture("testdata/textures/Aim.png"), glm::vec4(1, 1, 1, 1));
        renderer->drawCircle(glm::vec2(1280 - 200, 0), glm::vec2(200, 200), glm::vec4(1, 1, 0, 1));
        renderer->fillRect(glm::vec2(1280 - 400, 720 - 120), glm::vec2(400, 120), glm::vec4(1, 0.5f, 0, 1));
        renderer->fillRect(glm::vec2(1280 - 300, 720 - 120 - 120), glm::vec2(300, 120), glm::vec4(1, 0, 0, 1));
        // renderer->fillRect(glm::vec2(), glm::vec2(100, 100), glm::vec4(1, 0, 0, 1));
        renderer->end();
    }

private:
    ag::GameObject::Instance createDebri()
    {
        ag::GameObject::Instance ret = ag::GameObject::create("Debri");
        float pz = m_playerPosition.z;
        auto debri = std::make_shared<ag::ModelRenderer>(ret);
        debri->setModel(loadModel("testdata/models/Cube.fbx"));
        ret->setPosition({ ag::Random::range(-4, 4) * 3.0f, 0, pz - (ag::Random::range(4, 8) * 3.0f) });
        ret->setScale({ 0.01f, 0.01f, 0.01f });
        ret->addComponent(debri);
        return ret;
    }
    ag::GameObject::Instance createBullet()
    {
        ag::GameObject::Instance ret = ag::GameObject::create("Bullet");
        auto debri = std::make_shared<ag::ModelRenderer>(ret);
        auto bullet = std::make_shared<Bullet>(ret);
        bullet->setDirection({ 0, 0, -1 });
        bullet->setSpeed(20);
        debri->setModel(loadModel("testdata/models/Ball.fbx"));
        ret->setPosition(m_playerPosition);
        ret->setScale({ 0.01f, 0.01f, 0.01f });
        ret->addComponent(debri);
        ret->addComponent(bullet);
        return ret;
    }
    glm::vec3 m_playerPosition;
    float m_angle;
    float m_speed;
    std::vector<ag::GameObject::Instance> m_objects;
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(1280, 720, false, "ModelDraw");
}