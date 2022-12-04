#include <ag/graphics/mtl/MtlBufferPoolSet.hpp>
#include <ag/native/glm.hpp>

namespace ag {
MtlBufferPoolSet::MtlBufferPoolSet()
    : m_poolMap()
{
}
IBuffer::Instance MtlBufferPoolSet::rent(size_t size)
{
    if (!m_poolMap.count(size)) {
        m_poolMap.insert_or_assign(size, MtlBufferPool(static_cast<int>(size)));
    }
    return m_poolMap.at(size).rent();
}
void MtlBufferPoolSet::releaseAll()
{
    for (auto& kvp : m_poolMap) {
        kvp.second.releaseAll();
    }
}
}
