#include <ag/scene/SceneBase.hpp>

namespace ag {
SceneBase::SceneBase()
    : m_nextScene()
    , m_isFinished()
{
}

std::string SceneBase::getNextScene() const { return m_nextScene; }
bool SceneBase::isFinished() const { return m_isFinished; }
}