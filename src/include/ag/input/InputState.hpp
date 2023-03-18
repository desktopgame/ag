#pragma once
#include <ag/input/ButtonState.hpp>
#include <ag/input/IInputDetector.hpp>
#include <ag/input/KeyCode.hpp>
#include <ag/input/MouseButton.hpp>
#include <ag/native/glm.hpp>
#include <string>
#include <unordered_map>

namespace ag {
class KeyboardState {
public:
    friend class InputSystem;
    explicit KeyboardState();
    bool getKeyValue(KeyCode keyCode) const;
    ButtonState getKeyState(KeyCode keyCode) const;

private:
    bool m_currState[/* KeyCode::maxKeyCodeValue */ 512];
    bool m_prevState[/* KeyCode::maxKeyCodeValue */ 512];
};

class MouseState {
public:
    friend class InputSystem;
    explicit MouseState();
    glm::vec2 getPosition() const;
    glm::vec2 getScrollWheel() const;
    bool isRelative() const;

    bool getButtonValue(MouseButton button) const;
    ButtonState getButtonState(MouseButton button) const;

private:
    glm::vec2 m_mousePos;
    glm::vec2 m_scrollWheel;
    bool m_currButtons[3];
    bool m_prevButtons[3];
    bool m_isRelative;
};
class InputState {
public:
    InputState();

    bool getBoolValue(const std::string& name) const;
    ButtonState getButtonValue(const std::string& name) const;
    float getFloatValue(const std::string& name) const;
    glm::vec2 getAxisValue(const std::string& name) const;

    void putBinding(const std::string& key, const IInputDetector::Instance& detector);
    void removeBinding(const std::string& key);
    void clearBinding();

    KeyboardState& getKeyboardState();
    const KeyboardState& getKeyboardState() const;

    MouseState& getMouseState();
    const MouseState& getMouseState() const;

private:
    KeyboardState m_keyboardState;
    MouseState m_mouseState;
    std::unordered_map<std::string, IInputDetector::Instance> m_bindings;
};
}
