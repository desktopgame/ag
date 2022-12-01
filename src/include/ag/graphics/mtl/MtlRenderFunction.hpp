#pragma once
#ifdef AG_METAL
#include <ag/graphics/IRenderFunction.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/graphics/mtl/MtlBufferPool.hpp>
#include <ag/native/glfw.hpp>
#include <ag/native/metal.hpp>

namespace ag {
class MtlRenderFunction : public IRenderFunction {
public:
    explicit MtlRenderFunction(MtlBufferPool::Instance matrixPool, MtlBufferPool::Instance colorPool);
    ~MtlRenderFunction();
    void begin(const std::shared_ptr<Window>& window) override;
    void draw(const std::shared_ptr<RenderingObject>& object) override;
    void end(const std::shared_ptr<Window>& window) override;

private:
    MtlBufferPool::Instance m_matrixPool;
    MtlBufferPool::Instance m_colorPool;
    MTL::CommandBuffer* m_commandBuffer;
    CA::MetalDrawable* m_surface;
    MTL::RenderPassDescriptor* m_passDesc;
    MTL::RenderCommandEncoder* m_encoder;
};
}
#endif