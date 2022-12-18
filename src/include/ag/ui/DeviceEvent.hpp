#pragma once
#include <memory>

namespace agui {
class Component;
namespace DeviceEventType {
    inline const constexpr int None = 1 << 0;
    inline const constexpr int KeyEvent = 1 << 1;
    inline const constexpr int MouseEvent = 1 << 2;
};
class DeviceEvent : public std::enable_shared_from_this<DeviceEvent> {
public:
    using Instance = std::shared_ptr<DeviceEvent>;
    explicit DeviceEvent(const std::shared_ptr<Component>& source, int type);
    const std::shared_ptr<Component> source;
    const int type;

    void consume();
    bool isConsumed() const;

private:
    bool m_consumed;
};
}