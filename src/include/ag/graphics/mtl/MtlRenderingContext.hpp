#pragma once
#ifdef AG_METAL
#include <ag/graphics/RenderingContext.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
class MtlRenderingContext : public RenderingContext {
public:
    explicit MtlRenderingContext();
    ~MtlRenderingContext();
    void setup(const std::shared_ptr<IShader>& shader) override;
    void teardown(const std::shared_ptr<IShader>& shader) override;

private:
};
}
#endif