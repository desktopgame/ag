#pragma once
#ifdef AG_METAL
#include <ag/graphics/IRenderFunction.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/native/glfw.hpp>
#include <ag/native/metal.hpp>

namespace ag {
class MtlRenderFunction : public IRenderFunction {
public:
    explicit MtlRenderFunction();
    ~MtlRenderFunction();
    void begin(const std::shared_ptr<Window>& window) override;
    void draw(const std::shared_ptr<RenderingObject>& object) override;
    void end(const std::shared_ptr<Window>& window) override;

private:
    MTL::CommandBuffer* m_commandBuffer;
    CA::MetalDrawable* m_surface;
    MTL::RenderPassDescriptor* m_passDesc;
    MTL::RenderCommandEncoder* m_encoder;
};
}
#endif