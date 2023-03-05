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
    void link(const std::shared_ptr<Window>& window) override;
    void begin(const std::shared_ptr<Window>& window, const RenderPass& pass) override;
    void end() override;
    void clear(const std::shared_ptr<Window>& window) override;
    void present(const std::shared_ptr<Window>& window) override;
    void waitSync(const std::shared_ptr<Window>& window) override;
    MTL::RenderCommandEncoder* getRenderCommandEncoder() const;

private:
    MTL::RenderPassDescriptor* newRenderPassDescriptor(const std::shared_ptr<Window>& window);
    MTL::DepthStencilDescriptor* newDepthStencilDescriptor(const RenderPass& renderPass);
    MtlUniformManager::Instance m_uniformManager;
    MTL::CommandBuffer* m_commandBuffer;
    CA::MetalDrawable* m_surface;
    MTL::RenderCommandEncoder* m_encoder;
    NS::AutoreleasePool* m_arPool;
    bool m_shouldClear;
};
}
#endif