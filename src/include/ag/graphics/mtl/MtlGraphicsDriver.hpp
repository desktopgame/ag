#pragma once
#ifdef AG_METAL
#include <ag/graphics/IGraphicsDriver.hpp>

namespace ag {
class MtlGraphicsDriver : public IGraphicsDriver {
public:
    explicit MtlGraphicsDriver();
    void useWindowHint() override;
    void useContextExtension() override;
    std::shared_ptr<IGraphicsDevice> getGraphicsDevice() const override;
    std::shared_ptr<IShaderCompiler> getShaderCompiler() const override;
    std::shared_ptr<IRenderFunction> getRenderFunction() const override;

private:
};
}
#endif