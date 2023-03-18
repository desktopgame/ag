#include <ag/Window.hpp>
#include <ag/input/InputSystem.hpp>
namespace ag {
InputSystem::InputSystem(std::weak_ptr<Window> windowRef)
    : m_windowRef(windowRef)
    , m_inputState()
{
}

void InputSystem::scanEvents()
{
    auto& kb = m_inputState.getKeyboardState();
    auto& mouse = m_inputState.getMouseState();
    auto window = m_windowRef.lock();
    if (window->isDisposed()) {
        return;
    }
    // save mouse state
    std::memcpy(mouse.m_prevButtons, mouse.m_currButtons, sizeof(bool) * 3);
    // update mouse state
    mouse.m_currButtons[static_cast<int>(MouseButton::Left)] = window->isMousePress(MouseButton::Left);
    mouse.m_currButtons[static_cast<int>(MouseButton::Middle)] = window->isMousePress(MouseButton::Middle);
    mouse.m_currButtons[static_cast<int>(MouseButton::Right)] = window->isMousePress(MouseButton::Right);
    // save key state
    std::memcpy(kb.m_prevState, kb.m_currState, sizeof(bool) * KeyCode::maxKeyCodeValue);
    // update key state
    for (KeyCode kc : KeyCode::getKeys()) {
        if (kc.getValue() < 0)
            continue;
        kb.m_currState[kc.getValue()] = window->isKeyPress(kc);
    }
}

InputState& InputSystem::getInputState()
{
    return m_inputState;
}
const InputState& InputSystem::getInputState() const
{
    return m_inputState;
}
}
