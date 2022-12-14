#pragma once
#ifdef AG_METAL
#include <ag/graphics/mtl/MtlBufferPool.hpp>
#include <unordered_map>

namespace ag {
class MtlBufferPoolSet {
public:
    explicit MtlBufferPoolSet();

    IBuffer::Instance rent(size_t size);
    void releaseAll();

private:
    std::unordered_map<size_t, MtlBufferPool> m_poolMap;
};
}
#endif