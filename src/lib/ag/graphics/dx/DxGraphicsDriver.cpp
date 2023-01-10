#ifdef AG_DIRECT_X
#include <ag/graphics/dx/DxGraphicsDriver.hpp>
#include <string>

namespace ag {
DxGraphicsDriver::DxGraphicsDriver()
    : m_result(S_OK)
    , m_dxgiFactory(nullptr)
    , m_adaptors()
    , m_mainAdaptor(nullptr)
    , m_nativeDevice(nullptr)
{
    initFactory();
    initAdaptor();
    initFeatureLevel();
}
IDXGIFactory6* DxGraphicsDriver::getDXGIFactory() const { return m_dxgiFactory; }
// private
void DxGraphicsDriver::initFactory()
{
    if (FAILED(m_result)) {
        return;
    }
    UINT flags = 0;
#ifdef _DEBUG
    flags = DXGI_CREATE_FACTORY_DEBUG;
#endif
    m_result = CreateDXGIFactory2(flags, IID_PPV_ARGS(&m_dxgiFactory));
}
void DxGraphicsDriver::initAdaptor()
{
    if (FAILED(m_result)) {
        return;
    }
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
    if (FAILED(m_result)) {
        return;
    }
    D3D_FEATURE_LEVEL levels[] = {
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
    };
    D3D_FEATURE_LEVEL featureLevel;
    for (auto l : levels) {
        if (D3D12CreateDevice(m_mainAdaptor, l, IID_PPV_ARGS(&m_nativeDevice)) == S_OK) {
            featureLevel = l;
            break;
        }
    }
}
}
#endif