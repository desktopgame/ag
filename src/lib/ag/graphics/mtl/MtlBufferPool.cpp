#include <ag/Engine.hpp>
#include <ag/graphics/IGraphicsDevice.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/mtl/MtlBufferPool.hpp>

namespace ag {
MtlBufferPool::MtlBufferPool(int size)
    : m_size(size)
    , m_pool()
    , m_free()
{
}

IBuffer::Instance MtlBufferPool::rent()
{
    if (!m_free.empty()) {
        auto ret = m_free.front();
        m_pool.push_back(ret);
        m_free.pop();
        return ret;
    }
    auto buf = Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice()->newVertexBuffer();
    buf->allocate(m_size);
    m_pool.push_back(buf);
    return buf;
}

void MtlBufferPool::releaseAll()
{
    for (auto buf : m_pool) {
        m_free.push(buf);
    }
    m_pool.clear();
}
}