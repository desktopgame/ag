#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/IShader.hpp>
#include <ag/native/dx.hpp>

namespace ag {
class DxShader : public IShader {
public:
    explicit DxShader(ComPtr<ID3DBlob> vsBlob, ComPtr<ID3DBlob> psBlob);
    ~DxShader();
    void apply(const std::shared_ptr<ShaderParameter>& parameter) override;
    ComPtr<ID3DBlob> getVSBlob() const;
    ComPtr<ID3DBlob> getPSBlob() const;

private:
    ComPtr<ID3DBlob> m_vsBlob;
    ComPtr<ID3DBlob> m_psBlob;
};
}
#endif