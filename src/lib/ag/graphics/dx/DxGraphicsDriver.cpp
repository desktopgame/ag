#ifdef AG_DIRECT_X
#include <ag/graphics/dx/DxGraphicsDevice.hpp>
#include <ag/graphics/dx/DxGraphicsDriver.hpp>
#include <ag/native/glfw.hpp>
#include <stdexcept>
#include <string>

namespace ag {
DxGraphicsDriver::DxGraphicsDriver()
    : m_dxgiFactory(nullptr)
    , m_adaptors()
    , m_mainAdaptor(nullptr)
    , m_nativeDevice(nullptr)
    , m_device(nullptr)
{
    initFactory();
    initAdaptor();
    initFeatureLevel();
    m_device = std::make_shared<DxGraphicsDevice>(m_nativeDevice);
}
DxGraphicsDriver::~DxGraphicsDriver() { }
void DxGraphicsDriver::useWindowHint() { }
void DxGraphicsDriver::useContextExtension()
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}
std::shared_ptr<IGraphicsDevice> DxGraphicsDriver::getGraphicsDevice() const { return m_device; }
std::shared_ptr<IShaderCompiler> DxGraphicsDriver::getShaderCompiler() const { return nullptr; }
std::shared_ptr<IRenderFunction> DxGraphicsDriver::getRenderFunction() const { return nullptr; }
IDXGIFactory6* DxGraphicsDriver::getDXGIFactory() const { return m_dxgiFactory; }
// private
void DxGraphicsDriver::initFactory()
{
    UINT flags = 0;
#ifdef _DEBUG
    flags = DXGI_CREATE_FACTORY_DEBUG;
#endif
    if (FAILED(CreateDXGIFactory2(flags, IID_PPV_ARGS(&m_dxgiFactory)))) {
        throw std::runtime_error("failed CreateDXGIFactory2()");
    }
}
void DxGraphicsDriver::initAdaptor()
{
    for (int i = 0;
         m_dxgiFactory->EnumAdapters(i, &m_mainAdaptor) != DXGI_ERROR_NOT_FOUND;
         ++i) {
        m_adaptors.push_back(m_mainAdaptor);
    }
    for (auto adpt : m_adaptors) {
        DXGI_ADAPTER_DESC adesc = {};
        adpt->GetDesc(&adesc);
        std::wstring strDesc = adesc.Description;
        if (strDesc.find(L"Iris") != std::string::npos) {
            m_mainAdaptor = adpt;
            break;
        }
    }
}
void DxGraphicsDriver::initFeatureLevel()
{
    D3D_FEATURE_LEVEL levels[] = {
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
    };
    // D3D_FEATURE_LEVEL featureLevel;
    for (auto l : levels) {
        if (D3D12CreateDevice(m_mainAdaptor, l, IID_PPV_ARGS(&m_nativeDevice)) == S_OK) {
            // featureLevel = l;
            break;
        }
    }
}
}
#endif