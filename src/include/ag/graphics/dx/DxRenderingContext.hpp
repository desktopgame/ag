#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/RenderingContext.hpp>

namespace ag {
class DxRenderingContext : public RenderingContext {
public:
    explicit DxRenderingContext() = default;
    void draw(const std::shared_ptr<IShader>& shader, PrimitiveType primitiveType, int primCount) override;

private:
};
}
#endif