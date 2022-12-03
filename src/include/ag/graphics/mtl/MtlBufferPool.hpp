#pragma once
#include <ag/graphics/IBuffer.hpp>
#include <memory>
#include <queue>
#include <vector>

namespace ag {
class MtlBufferPool {
public:
    explicit MtlBufferPool(int size);
    IBuffer::Instance rent();
    void releaseAll();

private:
    int m_size;
    std::vector<IBuffer::Instance> m_pool;
    std::queue<IBuffer::Instance> m_free;
};
}