#ifdef AG_DIRECT_X
#include <ag/graphics/dx/DxTexture.hpp>

namespace ag {
void DxTexture::update(int width, int height, const uint8_t* pixels)
{
}
size_t DxTexture::getWidth() const { return 0; }
size_t DxTexture::getHeight() const { return 0; }
}
#endif