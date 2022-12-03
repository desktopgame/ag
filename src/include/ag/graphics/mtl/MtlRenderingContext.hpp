#pragma once
#ifdef AG_METAL
#include <ag/graphics/PrimitiveType.hpp>
#include <ag/graphics/RenderingContext.hpp>
#include <ag/native/glfw.hpp>
#include <ag/native/metal.hpp>

namespace ag {
class MtlRenderingContext : public RenderingContext {
public:
    explicit MtlRenderingContext();
    ~MtlRenderingContext();
    //void setup(const std::shared_ptr<IShader>& shader) override;
    void draw(MTL::RenderCommandEncoder* encoder, PrimitiveType type, int primCount);
    //void teardown(const std::shared_ptr<IShader>& shader) override;
    void draw(const std::shared_ptr<IShader>& shader, PrimitiveType primitiveType, int primCount) override;

private:
    static MTL::PrimitiveType convPrimitiveType(PrimitiveType type);
    MTL::RenderPipelineState* m_renderPipelineState;
};
}
#endif