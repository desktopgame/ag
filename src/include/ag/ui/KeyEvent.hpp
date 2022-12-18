#pragma once
#include <ag/native/glm.hpp>
#include <ag/ui/DeviceEvent.hpp>

namespace agui {
enum KeyAction {
    None,
    Type,
    Press,
    Release
};
class KeyEvent : public DeviceEvent {
public:
    explicit KeyEvent(const std::shared_ptr<Component>& source, char keyChar, int keyCode, KeyAction action);

    char keyChar;
    int keyCode;
    KeyAction action;

private:
};
}