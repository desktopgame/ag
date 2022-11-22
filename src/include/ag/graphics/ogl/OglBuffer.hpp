#pragma once
#include <ag/graphics/IBuffer.hpp>
#include <ag/native/glfw.hpp>
#include <cstddef>

namespace ag {
class OglBuffer : public IBuffer {
public:
    explicit OglBuffer();
    void allocate(size_t size) override;
    void update(const void* data) override;
    void release() override;

private:
    GLuint* m_res;
    size_t m_size;
};
}