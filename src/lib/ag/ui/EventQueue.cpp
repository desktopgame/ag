#include <ag/ui/EventQueue.hpp>

namespace agui {
EventQueue::Instance EventQueue::s_instance = nullptr;
EventQueue::Instance EventQueue::getInstance()
{
    if (!EventQueue::s_instance) {
        EventQueue::s_instance = std::shared_ptr<EventQueue>(new EventQueue());
    }
    return s_instance;
}

void EventQueue::post(const DeviceEvent::Instance& e)
{
    m_queue.push(e);
}
DeviceEvent::Instance EventQueue::take()
{
    DeviceEvent::Instance r = m_queue.front();
    m_queue.pop();
    return r;
}
bool EventQueue::canTake() const { return !m_queue.empty(); }

// private
EventQueue::EventQueue()
    : m_queue()
{
}
}