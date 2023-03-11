#ifdef AG_METAL
#include <ag/graphics/mtl/MtlTexture.hpp>
#include <vector>

namespace ag {
MtlTexture::MtlTexture(MTL::Device* device)
    : m_device(device)
    , m_nativeTexture()
    , m_width()
    , m_height()
{
}

MtlTexture::~MtlTexture()
{
    if (m_nativeTexture) {
        m_nativeTexture->release();
        m_nativeTexture = nullptr;
    }
}

void MtlTexture::init(int width, int height, const uint8_t* pixels)
{
    if (m_nativeTexture) {
        m_nativeTexture->release();
        m_nativeTexture = nullptr;
    }
    MTL::TextureDescriptor* desc = MTL::TextureDescriptor::alloc()->init();
    desc->setWidth(width);
    desc->setHeight(height);
    desc->setPixelFormat(MTL::PixelFormatRGBA8Unorm);
    desc->setTextureType(MTL::TextureType2D);
    desc->setStorageMode(MTL::StorageModeManaged);
    desc->setUsage(MTL::ResourceUsageSample | MTL::ResourceUsageRead);
    m_width = width;
    m_height = height;
    m_nativeTexture = m_device->newTexture(desc);
    int max = width * height * (32 /* bpp */ / 8);
    std::vector<uint8_t> tdata;
    tdata.reserve(width * height * 4);
    for (int i = 0; i < max;) {
        uint8_t r = pixels[i++];
        uint8_t g = pixels[i++];
        uint8_t b = pixels[i++];
        uint8_t a = 255;
        // if (colorType == ImageIO::COLOR_TYPE_A) {
        a = pixels[i++];
        //}
        tdata.emplace_back(r);
        tdata.emplace_back(g);
        tdata.emplace_back(b);
        tdata.emplace_back(a);
    }
    m_nativeTexture->replaceRegion(MTL::Region(0, 0, 0, width, height, 1), 0,
        tdata.data(), width * 4);
    desc->release();
}
int MtlTexture::getWidth() const { return m_width; }
int MtlTexture::getHeight() const { return m_height; }
void MtlTexture::attach(MTL::RenderCommandEncoder* encoder, int index)
{
    encoder->setFragmentTexture(m_nativeTexture, index);
}
}
#endif