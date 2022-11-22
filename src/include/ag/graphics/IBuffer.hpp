#pragma once
#include <memory>

namespace ag {
class IBuffer {
public:
    using Instance = std::shared_ptr<IBuffer>;
    IBuffer() = default;
    virtual ~IBuffer() = default;
    virtual void allocate(size_t size) = 0;
    virtual void update(const void* data) = 0;
    virtual void release() = 0;
};
}