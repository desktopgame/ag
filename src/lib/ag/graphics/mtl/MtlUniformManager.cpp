#include <ag/graphics/mtl/MtlUniformManager.hpp>
#include <ag/native/glm.hpp>

namespace ag {
const int MtlUniformManager::Count = 3;
MtlUniformManager::MtlUniformManager()
    : m_index()
    , m_poolSet()
#ifdef STD_SEMAPHORE
    , m_semaphore(MtlUniformManager::Count)
#endif
{
#ifndef STD_SEMAPHORE
    m_nsSemaphore = dispatch_semaphore_create(MtlUniformManager::Count);
#endif
}
IBuffer::Instance MtlUniformManager::rentTransformBuffer() { return m_poolSet.at(m_index).rent(sizeof(glm::mat4)); }
IBuffer::Instance MtlUniformManager::rentColorBuffer() { return m_poolSet.at(m_index).rent(sizeof(glm::vec4)); }
void MtlUniformManager::releaseAll() { m_poolSet.at(m_index).releaseAll(); }
void MtlUniformManager::next()
{
    m_index = (m_index + 1) % MtlUniformManager::Count;
}
void MtlUniformManager::waitSync()
{
#ifdef STD_SEMAPHORE
    m_semaphore.acquire();
#else
    dispatch_semaphore_wait(m_nsSemaphore, DISPATCH_TIME_FOREVER);
#endif
}
void MtlUniformManager::signal()
{
#ifdef STD_SEMAPHORE
    m_semaphore.release();
#else
    dispatch_semaphore_signal(m_nsSemaphore);
#endif
}
}