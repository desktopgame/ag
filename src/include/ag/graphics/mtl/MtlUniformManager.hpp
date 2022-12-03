#pragma once
#include <ag/graphics/mtl/MtlBufferPoolSet.hpp>
#include <array>
#include <memory>
#include <semaphore>

namespace ag {
class MtlUniformManager {
public:
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
    std::counting_semaphore<3> m_semaphore;
};
}