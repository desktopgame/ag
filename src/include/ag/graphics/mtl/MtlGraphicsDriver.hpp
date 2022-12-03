#pragma once
#ifdef AG_METAL
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/mtl/MtlBufferPool.hpp>
#include <ag/graphics/mtl/MtlUniformManager.hpp>
#include <ag/native/metal.hpp>

namespace ag {
class MtlGraphicsDriver : public IGraphicsDriver {
public:
    explicit MtlGraphicsDriver();
    ~MtlGraphicsDriver();
    void useWindowHint() override;
    void useContextExtension() override;
    std::shared_ptr<IGraphicsDevice> getGraphicsDevice() const override;
    std::shared_ptr<IShaderCompiler> getShaderCompiler() const override;
    std::shared_ptr<IRenderFunction> getRenderFunction() const override;

    void useDevice(CA::MetalLayer* metalLayer);

private:
    MTL::Device* m_nativeDevice;
    std::shared_ptr<IGraphicsDevice> m_device;
    std::shared_ptr<IShaderCompiler> m_shaderCompiler;
    std::shared_ptr<IRenderFunction> m_renderFunction;
    MtlUniformManager::Instance m_uniformManager;
};
}
#endif