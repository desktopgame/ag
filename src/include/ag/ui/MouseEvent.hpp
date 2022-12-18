#pragma once
#include <ag/native/glm.hpp>
#include <ag/ui/DeviceEvent.hpp>

namespace agui {
enum MouseAction {
    None,
    Press,
    Release
};
class MouseEvent : public DeviceEvent {
public:
    explicit MouseEvent(const std::shared_ptr<Component>& source, const glm::ivec2& position, int button, MouseAction action);

    glm::ivec2 position;
    int button;
    MouseAction action;

private:
};
}