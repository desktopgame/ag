#pragma once
#include <ag/input/ButtonState.hpp>
#include <ag/native/glm.hpp>
#include <memory>

namespace ag {
class IInputDetector : public std::enable_shared_from_this<IInputDetector> {
public:
    using Reference = std::weak_ptr<IInputDetector>;
    using Instance = std::shared_ptr<IInputDetector>;
    explicit IInputDetector() = default;

    virtual ~IInputDetector() = default;
    virtual bool getBoolValue(const class InputState& state) const = 0;
    virtual ButtonState getButtonValue(const class InputState& state) const = 0;
    virtual float getFloatValue(const class InputState& state) const = 0;
    virtual glm::vec2 getAxisValue(const class InputState& state) const = 0;

private:
};
}
