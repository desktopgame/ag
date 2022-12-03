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
    void draw(const std::shared_ptr<IShader>& shader, PrimitiveType primitiveType, int primCount) override;

private:
    void createRenderPipelineState(const std::shared_ptr<IShader>& shader);
    static MTL::PrimitiveType convPrimitiveType(PrimitiveType type);
    MTL::RenderPipelineState* m_renderPipelineState;
};
}
#endif