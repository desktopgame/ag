#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/IShader.hpp>
#include <ag/native/dx.hpp>

namespace ag {
class DxShader : public IShader {
public:
    explicit DxShader(ID3DBlob* vsBlob, ID3DBlob* psBlob);
    ~DxShader();
    void apply(const std::shared_ptr<ShaderParameter>& parameter) override;
    ID3DBlob* getVSBlob() const;
    ID3DBlob* getPSBlob() const;

private:
    ID3DBlob* m_vsBlob;
    ID3DBlob* m_psBlob;
};
}
#endif