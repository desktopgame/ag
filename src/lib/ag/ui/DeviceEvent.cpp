#include <ag/ui/DeviceEvent.hpp>

namespace agui {
DeviceEvent::DeviceEvent(std::shared_ptr<Component> source, DeviceEventType type)
    : source(source)
    , type(type)
    , m_consumed()
{
}

void DeviceEvent::consume() { m_consumed = true; }
bool DeviceEvent::isConsumed() const { return m_consumed; }
}