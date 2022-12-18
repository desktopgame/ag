#include <ag/ui/MouseEvent.hpp>

namespace agui {
MouseEvent::MouseEvent(const std::shared_ptr<Component>& source, const glm::ivec2& position, int button, MouseAction action)
    : DeviceEvent(source, DeviceEventType::MouseEvent)
    , position(position)
    , button(button)
    , action(action)
{
}
}