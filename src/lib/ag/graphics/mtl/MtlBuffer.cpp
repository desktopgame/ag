#include <ag/graphics/mtl/MtlBuffer.hpp>
#ifdef AG_METAL

namespace ag {
MtlBuffer::MtlBuffer(bool indexMode)
//: m_indexMode(indexMode)
{
}
void MtlBuffer::allocate(size_t size) { }
void MtlBuffer::update(const void* data) { }
void MtlBuffer::release() { }
}
#endif