#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/ITexture.hpp>
#include <ag/native/dx.hpp>

namespace ag {
class DxTexture : public ITexture {
public:
    explicit DxTexture(ComPtr<ID3D12Device> device);

    void init(int width, int height, const uint8_t* pixels);
    int getWidth() const override;
    int getHeight() const override;
    ComPtr<ID3D12Resource> getResource() const;

private:
    int m_width;
    int m_height;
    ComPtr<ID3D12Device> m_device;
    ComPtr<ID3D12Resource> m_resource;
};
}
#endif