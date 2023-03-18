#pragma once
#include <ag/scene/IScene.hpp>

namespace ag {
class SceneBase : public IScene {
public:
    explicit SceneBase();
    virtual ~SceneBase() = default;

    std::string getNextScene() const override;
    bool isFinished() const override;

protected:
    std::string m_nextScene;
    bool m_isFinished;

private:
};
}