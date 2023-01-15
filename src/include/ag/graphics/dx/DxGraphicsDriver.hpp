#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/IGraphicsDevice.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/native/dx.hpp>
#include <vector>

namespace ag {
class DxGraphicsDriver : public IGraphicsDriver {
public:
    explicit DxGraphicsDriver();
    ~DxGraphicsDriver();
    void useWindowHint() override;
    void useContextExtension() override;
    std::shared_ptr<IGraphicsDevice> getGraphicsDevice() const override;
    std::shared_ptr<IShaderCompiler> getShaderCompiler() const override;
    std::shared_ptr<IRenderFunction> getRenderFunction() const override;
    IDXGIFactory6* getDXGIFactory() const;

private:
    void initFactory();
    void initAdaptor();
    void initFeatureLevel();

    IDXGIFactory6* m_dxgiFactory;
    std::vector<IDXGIAdapter*> m_adaptors;
    IDXGIAdapter* m_mainAdaptor;
    ID3D12Device* m_nativeDevice;
    std::shared_ptr<IGraphicsDevice> m_device;
    std::shared_ptr<IShaderCompiler> m_shaderCompiler;
    std::shared_ptr<IRenderFunction> m_renderFunction;
};
}
#endif