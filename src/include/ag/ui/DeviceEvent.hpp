#pragma once
#include <memory>

namespace agui {
class Component;
enum class DeviceEventType {
    None = 1 << 0,
    KeyEvent = 1 << 1,
    MouseEvent = 1 << 2,
};
class DeviceEvent : public std::enable_shared_from_this<DeviceEventType> {
public:
    using Instance = std::shared_ptr<DeviceEvent>;
    explicit DeviceEvent(std::shared_ptr<Component> source, DeviceEventType type);
    const std::shared_ptr<Component> source;
    const DeviceEventType type;

    void consume();
    bool isConsumed() const;

private:
    bool m_consumed;
};
}