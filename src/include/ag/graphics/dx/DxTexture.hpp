#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/ITexture.hpp>
#include <ag/native/dx.hpp>

namespace ag {
class DxTexture : public ITexture {
public:
    explicit DxTexture(ID3D12Device* device);

    void update(int width, int height, const uint8_t* pixels) override;
    size_t getWidth() const override;
    size_t getHeight() const override;

private:
    int m_width;
    int m_height;
    ID3D12Device* m_device;
    ID3D12Resource* m_resource;
};
}
#endif