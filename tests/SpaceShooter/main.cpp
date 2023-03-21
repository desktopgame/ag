#include "Bullet.hpp"
#include "Player.hpp"
#include <ag/agOne.hpp>
#include <ag/easy/App.hpp>
#include <ag/graphics/Model.hpp>
#include <ag/native/glm.hpp>
#include <ag/object/GameObjectCollection.hpp>
#include <ag/object/ModelRenderer.hpp>
#include <ag/util/Random.hpp>
#include <cassert>

class MyApp : public ag::easy::App {
public:
    MyApp(int argc, char* argv[])
        : App(argc, argv)
        , m_player()
        , m_gameObjectCollection()
    {
    }
    void start(const ag::Window::Instance& window, const ag::InputState& input, const ag::Renderer::Instance& renderer)
    {
        auto playerObject = m_gameObjectCollection.create("Player");
        m_player = std::make_shared<Player>(playerObject);
        m_player->setup(m_gameObjectCollection, loadModel("testdata/models/Ball.fbx"));
        playerObject->addComponent(m_player);
        for (int i = 0; i < 10; i++) {
            createDebri();
        }
    }

    void update(const ag::Window::Instance& window, const ag::InputState& input, const ag::Renderer::Instance& renderer)
    {
        auto engine = ag::Engine::getInstance();
        auto looper = engine->getLooper();
        // 3D rendering
        renderer->begin(window, ag::RenderPass::default3D());
        renderer->lookAt(m_player->getGameObject()->getPosition(), m_player->getGameObject()->getPosition() + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

        size_t size = m_gameObjectCollection.size();
        m_gameObjectCollection.update(input, looper->deltaTime());
        m_gameObjectCollection.draw(renderer);

        while (m_gameObjectCollection.size() < size) {
            createDebri();
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
    void createDebri()
    {
        ag::GameObject::Instance ret = m_gameObjectCollection.create("Debri");
        float pz = m_player->getGameObject()->getPosition().z;
        auto debri = std::make_shared<ag::ModelRenderer>(ret);
        debri->setModel(loadModel("testdata/models/Cube.fbx"));
        ret->setPosition({ ag::Random::range(-4, 4) * 3.0f, 0, pz - (ag::Random::range(4, 8) * 3.0f) });
        ret->setScale({ 0.01f, 0.01f, 0.01f });
        ret->addComponent(debri);
    }
    std::shared_ptr<Player> m_player;
    ag::GameObjectCollection m_gameObjectCollection;
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(1280, 720, false, "ModelDraw");
}