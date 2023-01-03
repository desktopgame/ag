#ifdef AG_METAL
#include <ag/graphics/mtl/MtlBuffer.hpp>

namespace ag {
MtlBuffer::MtlBuffer(MTL::Device* device)
    : m_device(device)
    , m_buffer(nullptr)
    , m_size()
{
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
void MtlBuffer::attachAsVertex(MTL::RenderCommandEncoder* encoder, int offset, int index)
{
    encoder->setVertexBuffer(m_buffer, offset, index);
}
void MtlBuffer::attachAsFragment(MTL::RenderCommandEncoder* encoder, int offset, int index)
{
    encoder->setFragmentBuffer(m_buffer, offset, index);
}
void MtlBuffer::drawWithIndex(MTL::RenderCommandEncoder* encoder, MTL::PrimitiveType primitiveType, int indexLength)
{
    encoder->drawIndexedPrimitives(primitiveType, indexLength,
        MTL::IndexType::IndexTypeUInt32, m_buffer,
        0);
}
}
#endif