#ifdef AG_DIRECT_X
#include <ag/graphics/dx/DxShader.hpp>

namespace ag {
int DxShader::s_uid = 0;
DxShader::DxShader(ID3DBlob* vsBlob, ID3DBlob* psBlob)
    : m_vsBlob(vsBlob)
    , m_psBlob(psBlob)
    , m_uid(s_uid++)
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
int DxShader::getUID() const { return m_uid; }
}
#endif