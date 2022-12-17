#pragma once
#include <ag/ui/DeviceEvent.hpp>
#include <memory>
#include <queue>

namespace agui {
class EventQueue {
public:
    using Instance = std::shared_ptr<EventQueue>;
    static Instance getInstance();

    void post(const DeviceEvent::Instance& e);

    DeviceEvent::Instance take();
    bool canTake() const;

private:
    EventQueue();
    static std::shared_ptr<EventQueue> s_instance;
    std::queue<DeviceEvent::Instance> m_queue;
};
}
