#include <ag/ui/KeyEvent.hpp>

namespace agui {
KeyEvent::KeyEvent(const std::shared_ptr<Component>& source, char keyChar, int keyCode, KeyAction action)
    : DeviceEvent(source, DeviceEventType::KeyEvent)
    , keyChar(keyChar)
    , keyCode(keyCode)
    , action(action)
{
}
}