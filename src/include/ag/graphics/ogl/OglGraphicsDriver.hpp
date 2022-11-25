#pragma once
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/ogl/OglGraphicsDevice.hpp>

namespace ag {
class OglGraphicsDriver : public IGraphicsDriver {
public:
    explicit OglGraphicsDriver();
    void useWindowHint() override;
    void useContextExtension() override;
    std::shared_ptr<IGraphicsDevice> getGraphicsDevice() const override;
    std::shared_ptr<IShaderCompiler> getShaderCompiler() const override;

private:
    std::shared_ptr<IGraphicsDevice> m_device;
    std::shared_ptr<IShaderCompiler> m_shaderCompiler;
};
}