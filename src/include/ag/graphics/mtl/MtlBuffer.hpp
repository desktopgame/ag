#pragma once
#include <ag/graphics/IBuffer.hpp>
#include <ag/native/glfw.hpp>
#include <cstddef>

namespace ag {
class MtlBuffer : public IBuffer {
public:
    explicit MtlBuffer(bool indexMode);
    void allocate(size_t size) override;
    void update(const void* data) override;
    void release() override;

private:
    //bool m_indexMode;
};
}