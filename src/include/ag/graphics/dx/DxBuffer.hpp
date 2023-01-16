#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/IBuffer.hpp>
#include <ag/native/dx.hpp>

namespace ag {
class DxBuffer : public IBuffer {
public:
    explicit DxBuffer(ID3D12Device* device);
    ~DxBuffer();

    void allocate(size_t size) override;
    void update(const void* data) override;
    void release() override;

private:
    ID3D12Device* m_device;
    ID3D12Resource* m_resource;
    size_t m_size;
};
}
#endif