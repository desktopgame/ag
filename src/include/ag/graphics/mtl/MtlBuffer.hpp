#pragma once
#ifdef AG_METAL
#include <ag/graphics/IBuffer.hpp>
#include <ag/native/glfw.hpp>
#include <ag/native/metal.hpp>
#include <cstddef>

namespace ag {
class MtlBuffer : public IBuffer {
public:
    explicit MtlBuffer(MTL::Device* device);
    ~MtlBuffer();
    void allocate(size_t size) override;
    void update(const void* data) override;
    void release() override;

private:
    MTL::Device* m_device;
    MTL::Buffer* m_buffer;
    size_t m_size;
};
}
#endif