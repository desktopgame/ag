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
    int getUID() const;

private:
    ID3DBlob* m_vsBlob;
    ID3DBlob* m_psBlob;
    int m_uid;
    static int s_uid;
};
}
#endif