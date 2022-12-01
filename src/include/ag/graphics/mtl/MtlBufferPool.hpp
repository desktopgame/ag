#pragma once
#include <ag/graphics/IBuffer.hpp>
#include <memory>
#include <queue>
#include <vector>

namespace ag {
class MtlBufferPool {
public:
    using Instance = std::shared_ptr<MtlBufferPool>;
    explicit MtlBufferPool(int size);
    IBuffer::Instance rent();
    void release();

private:
    int m_size;
    std::vector<IBuffer::Instance> m_pool;
    std::queue<IBuffer::Instance> m_free;
};
}