#include <ag/Engine.hpp>
#include <ag/ImageIO.hpp>
#include <ag/native/freeimage.hpp>

namespace ag {
// Pixel
Pixel::Pixel()
    : r(0)
    , g(0)
    , b(0)
    , a(0)
{
}
// Image
Image::Image()
    : width(0)
    , height(0)
    , pixels()
{
}

const uint8_t* Image::getData() const
{
    const auto& first = pixels.front();
    return &first.r;
}
// ImageIO
bool ImageIO::s_initialized = false;

void ImageIO::initialize()
{
    if (!s_initialized) {
        s_initialized = true;
        FreeImage_Initialise();
    }
}

bool ImageIO::load(uint8_t* binary, ImageFormat format, Image& outImage)
{
    Engine::require();
    FIMEMORY* mem = FreeImage_OpenMemory(binary);
    if (mem == nullptr) {
        return false;
    }
    FREE_IMAGE_FORMAT fmt = static_cast<FREE_IMAGE_FORMAT>(toFreeImageFormat(format));
    FIBITMAP* dib = FreeImage_LoadFromMemory(fmt, mem);
    if (dib == nullptr) {
        return false;
    }
    loadImpl(dib, outImage);
    FreeImage_CloseMemory(mem);
    return true;
}

bool ImageIO::load(const std::string& file, ImageFormat format, Image& outImage)
{
    Engine::require();
    FIBITMAP* dib = FreeImage_Load(static_cast<FREE_IMAGE_FORMAT>(toFreeImageFormat(format)), file.c_str());
    if (dib == nullptr) {
        return false;
    }
    loadImpl(dib, outImage);
    return true;
}

void ImageIO::destroy()
{
    if (s_initialized) {
        s_initialized = false;
        FreeImage_DeInitialise();
    }
}

// private
void ImageIO::loadImpl(void* vdib, Image& outImage)
{
    FIBITMAP* dib = reinterpret_cast<FIBITMAP*>(vdib);
    FreeImage_FlipVertical(dib);
    uint8_t* bits = FreeImage_GetBits(dib);
    int width = static_cast<int>(FreeImage_GetWidth(dib));
    int height = static_cast<int>(FreeImage_GetHeight(dib));
    int colorType = static_cast<int>(FreeImage_GetColorType(dib));
    // determine components.
    int components = -1;
    if (colorType == FIC_RGB) {
        components = 3;
    } else if (colorType == FIC_RGBALPHA) {
        components = 4;
    } else {
        throw std::runtime_error("invald components.");
    }
    // construct image data.
    outImage.width = width;
    outImage.height = height;
    Pixel pix;
    int max = width * height * components;
    for (int i = 0; i < max;) {
        pix.b = bits[i++];
        pix.g = bits[i++];
        pix.r = bits[i++];
        pix.a = 255;
        if (colorType == FIC_RGBALPHA) {
            pix.a = bits[i++];
        }
        outImage.pixels.push_back(pix);
    }
    FreeImage_Unload(dib);
}
int ImageIO::toFreeImageFormat(ImageFormat format)
{
    switch (format) {
    case ImageFormat::BMP:
        return FIF_BMP;
    case ImageFormat::JPG:
        return FIF_JPEG;
    case ImageFormat::JPEG:
        return FIF_JPEG;
    case ImageFormat::PNG:
        return FIF_PNG;
    case ImageFormat::GIF:
        return FIF_GIF;
    }
    return -1;
}
}