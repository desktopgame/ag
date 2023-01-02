#pragma once
#ifdef AG_METAL
#include <ag/graphics/IRenderFunction.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/graphics/mtl/MtlBufferPool.hpp>
#include <ag/graphics/mtl/MtlUniformManager.hpp>
#include <ag/native/glfw.hpp>
#include <ag/native/metal.hpp>

namespace ag {
class MtlRenderFunction : public IRenderFunction {
public:
    explicit MtlRenderFunction(MtlUniformManager::Instance uniformManager);
    ~MtlRenderFunction();
    void begin(const std::shared_ptr<Window>& window, const RenderPass& pass) override;
    void end() override;
    MTL::RenderCommandEncoder* getRenderCommandEncoder() const;

private:
    MTL::RenderPassDescriptor* allocRenderPassDescriptor(const std::shared_ptr<Window>& window);
    MtlUniformManager::Instance m_uniformManager;
    MTL::CommandBuffer* m_commandBuffer;
    CA::MetalDrawable* m_surface;
    MTL::RenderCommandEncoder* m_encoder;
    NS::AutoreleasePool* m_arPool;
};
}
#endif