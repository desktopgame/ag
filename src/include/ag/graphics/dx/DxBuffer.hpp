#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/IBuffer.hpp>

namespace ag {
class DxBuffer : public IBuffer {
public:
    explicit DxBuffer() = default;

    void allocate(size_t size) override;
    void update(const void* data) override;
    void release() override;

private:
};
}
#endif