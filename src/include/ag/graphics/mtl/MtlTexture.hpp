#pragma once
#ifdef AG_METAL
#include <ag/graphics/ITexture.hpp>
#include <ag/native/metal.hpp>

namespace ag {
class MtlTexture : public ITexture {
public:
    explicit MtlTexture(MTL::Device* device);
    ~MtlTexture();

    void update(int width, int height, const uint8_t* pixels) override;
    size_t getWidth() const override;
    size_t getHeight() const override;

    void attach(MTL::RenderCommandEncoder* encoder, int index);

private:
    MTL::Device* m_device;
    MTL::Texture* m_nativeTexture;
    int m_width;
    int m_height;
};
}
#endif