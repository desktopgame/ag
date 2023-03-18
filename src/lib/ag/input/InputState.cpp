#include <ag/input/InputState.hpp>

namespace ag {
// KeyboardState
KeyboardState::KeyboardState()
    : m_currState()
    , m_prevState()
{
    std::memset(m_currState, 0, KeyCode::maxKeyCodeValue);
    std::memset(m_prevState, 0, KeyCode::maxKeyCodeValue);
}
bool KeyboardState::getKeyValue(int keyCode) const { return m_currState[keyCode]; }
ButtonState KeyboardState::getKeyState(int keyCode) const
{
    if (!m_prevState[keyCode]) {
        if (!m_currState[keyCode]) {
            return ButtonState::None;
        } else {
            return ButtonState::Pressed;
        }
    } else {
        if (!m_currState[keyCode]) {
            return ButtonState::Released;
        } else {
            return ButtonState::Held;
        }
    }
}
// MouseState
MouseState::MouseState()
    : m_mousePos()
    , m_scrollWheel()
    , m_currButtons()
    , m_prevButtons()
    , m_isRelative()
{
}
glm::vec2 MouseState::getPosition() const
{
    return m_mousePos;
}
glm::vec2 MouseState::getScrollWheel() const
{
    return m_scrollWheel;
}
bool MouseState::isRelative() const
{
    return m_isRelative;
}

bool MouseState::getButtonValue(MouseButton button) const
{
    return m_currButtons[static_cast<int>(button)];
}
ButtonState MouseState::getButtonState(MouseButton button) const
{
    int i = static_cast<int>(button);
    if (m_prevButtons[i]) {
        if (m_currButtons[i]) {
            return ButtonState::Held;
        } else {
            return ButtonState::Released;
        }
    } else {
        if (m_currButtons[i]) {
            return ButtonState::Pressed;
        } else {
            return ButtonState::None;
        }
    }
}
// InputState

InputState::InputState()
    : m_keyboardState()
    , m_mouseState()
    , m_bindings()
{
}

bool InputState::getBoolValue(const std::string& name) const
{
    return m_bindings.at(name)->getBoolValue(*this);
}
ButtonState InputState::getButtonValue(const std::string& name) const
{
    return m_bindings.at(name)->getButtonValue(*this);
}
float InputState::getFloatValue(const std::string& name) const
{
    return m_bindings.at(name)->getFloatValue(*this);
}
glm::vec2 InputState::getAxisValue(const std::string& name) const
{
    return m_bindings.at(name)->getAxisValue(*this);
}

void InputState::putBinding(const std::string& key, const IInputDetector::Instance& detector)
{
    m_bindings[key] = detector;
}
void InputState::removeBinding(const std::string& key)
{
    m_bindings.erase(key);
}
void InputState::clearBinding()
{
    m_bindings.clear();
}

KeyboardState& InputState::getKeyboardState() { return m_keyboardState; }
const KeyboardState& InputState::getKeyboardState() const { return m_keyboardState; }

MouseState& InputState::getMouseState() { return m_mouseState; }
const MouseState& InputState::getMouseState() const { return m_mouseState; }
}
