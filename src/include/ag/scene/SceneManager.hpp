#pragma once
#include <ag/scene/IScene.hpp>
#include <string>
#include <unordered_map>

namespace ag {
class SceneManager {
public:
    explicit SceneManager(const std::unordered_map<std::string, IScene::Instance>& map);

    void start(const std::string& name);
    void update(const InputState& input, float deltaTime);
    void draw(const Renderer::Instance& renderer);

private:
    std::string m_current;
    std::unordered_map<std::string, IScene::Instance> m_map;
};
}