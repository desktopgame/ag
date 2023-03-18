#pragma once
#include <ag/graphics/Renderer.hpp>
#include <ag/input/InputState.hpp>
#include <memory>

namespace ag {
class IScene {
public:
    using Instance = std::shared_ptr<IScene>;
    explicit IScene() = default;
    virtual ~IScene() = default;
    virtual void show() = 0;
    virtual void update(const InputState& input, float deltaTime) = 0;
    virtual void draw(const Renderer::Instance& renderer) = 0;
    virtual void hide() = 0;

    virtual std::string getNextScene() const = 0;
    virtual bool isFinished() const = 0;
};
}