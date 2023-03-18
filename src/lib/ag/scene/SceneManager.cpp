#include <ag/scene/SceneManager.hpp>

namespace ag {
SceneManager::SceneManager(const std::unordered_map<std::string, IScene::Instance>& map)
    : m_current("")
    , m_map(map)
{
}

void SceneManager::start(const std::string& name)
{
    m_current = name;
    m_map[m_current]->show();
}
void SceneManager::update(const InputState& input, float deltaTime)
{
    if (m_current.empty()) {
        return;
    }
    m_map[m_current]->update(input, deltaTime);
    if (m_map[m_current]->isFinished()) {
        m_map[m_current]->hide();
        m_current = m_map[m_current]->getNextScene();
        m_map[m_current]->show();
    }
}
void SceneManager::draw(const Renderer::Instance& renderer)
{
    if (m_current.empty()) {
        return;
    }
    m_map[m_current]->draw(renderer);
}
}