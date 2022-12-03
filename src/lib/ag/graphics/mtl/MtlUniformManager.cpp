#include <ag/graphics/mtl/MtlUniformManager.hpp>
#include <ag/native/glm.hpp>

namespace ag {
MtlUniformManager::MtlUniformManager()
    : m_index()
    , m_poolSet()
    , m_semaphore(3)
{
}
IBuffer::Instance MtlUniformManager::rentTransformBuffer() { return m_poolSet.at(m_index).rent(sizeof(glm::mat4)); }
IBuffer::Instance MtlUniformManager::rentColorBuffer() { return m_poolSet.at(m_index).rent(sizeof(glm::vec4)); }
void MtlUniformManager::releaseAll() { m_poolSet.at(m_index).releaseAll(); }
void MtlUniformManager::next()
{
    m_index = (m_index + 1) % 3;
}
void MtlUniformManager::waitSync() { m_semaphore.acquire(); }
void MtlUniformManager::signal() { m_semaphore.release(); }
}