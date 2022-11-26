#include <ag/graphics/mtl/MtlBuffer.hpp>
#ifdef AG_METAL

namespace ag {
MtlBuffer::MtlBuffer(MTL::Device* device, bool indexMode)
    : m_indexMode(indexMode)
    , m_device(device)
    , m_buffer(nullptr)
    , m_size()
{
    m_device->retain();
}
MtlBuffer::~MtlBuffer()
{
    m_device->release();
    release();
}
void MtlBuffer::allocate(size_t size)
{
    if (!m_buffer) {
        m_buffer = m_device->newBuffer(size, MTL::ResourceStorageModeManaged);
        m_size = size;
    }
}
void MtlBuffer::update(const void* data)
{
    ::memcpy(m_buffer->contents(), data, m_size);
    m_buffer->didModifyRange(NS::Range(0, m_size));
}
void MtlBuffer::release()
{
    if (m_buffer) {
        m_buffer->release();
        m_buffer = nullptr;
    }
}
}
#endif