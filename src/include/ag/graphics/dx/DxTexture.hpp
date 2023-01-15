#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/ITexture.hpp>

namespace ag {
class DxTexture : public ITexture {
public:
    explicit DxTexture() = default;

    void update(int width, int height, const uint8_t* pixels) override;
    size_t getWidth() const override;
    size_t getHeight() const override;

private:
};
}
#endif