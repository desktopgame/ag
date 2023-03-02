#ifdef AG_DIRECT_X
#include <ag/graphics/dx/DxShader.hpp>

namespace ag {
DxShader::DxShader(ComPtr<ID3DBlob> vsBlob, ComPtr<ID3DBlob> psBlob)
    : m_vsBlob(vsBlob)
    , m_psBlob(psBlob)
{
}
DxShader::~DxShader()
{
    m_vsBlob->Release();
    m_psBlob->Release();
}
void DxShader::apply(const std::shared_ptr<ShaderParameter>& parameter)
{
}

ComPtr<ID3DBlob> DxShader::getVSBlob() const { return m_vsBlob; }
ComPtr<ID3DBlob> DxShader::getPSBlob() const { return m_psBlob; }
}
#endif