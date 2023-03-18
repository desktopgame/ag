#pragma once
#include <ag/input/InputState.hpp>
#include <ag/native/glm.hpp>
#include <memory>
#include <string>

namespace ag {
class Window;
class InputSystem {
public:
    using Reference = std::weak_ptr<InputSystem>;
    using Instance = std::shared_ptr<InputSystem>;
    explicit InputSystem(std::weak_ptr<Window> windowRef);

    void scanEvents();

    InputState& getInputState();
    const InputState& getInputState() const;

private:
    std::weak_ptr<Window> m_windowRef;
    InputState m_inputState;
};
}
