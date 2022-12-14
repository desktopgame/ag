#pragma once
#ifdef AG_METAL
#include <ag/graphics/mtl/MtlBufferPoolSet.hpp>
#include <ag/native/metal.hpp>
#include <array>
#include <memory>
#include <semaphore>

#define STD_SEMAPHORE

namespace ag {
class MtlUniformManager {
public:
    static const int Count;
    using Instance = std::shared_ptr<MtlUniformManager>;
    explicit MtlUniformManager();
    IBuffer::Instance rentTransformBuffer();
    IBuffer::Instance rentColorBuffer();
    void releaseAll();
    void next();

    void waitSync();
    void signal();

private:
    int m_index;
    std::array<MtlBufferPoolSet, 3> m_poolSet;
#ifdef STD_SEMAPHORE
    std::counting_semaphore<3> m_semaphore;
#else
    dispatch_semaphore_t m_nsSemaphore;
#endif
};
}
#endif