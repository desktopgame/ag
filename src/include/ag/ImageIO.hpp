#pragma once
#include <string>
#include <vector>

namespace ag {
enum class ImageFormat {
    BMP,
    JPG,
    JPEG,
    PNG,
    GIF
};
struct Pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    explicit Pixel();
};
struct Image {
    int width;
    int height;
    int bpp;
    std::vector<Pixel> pixels;

    explicit Image();
    const uint8_t* getData() const;
};
class ImageIO {
public:
    static void initialize();
    static bool load(uint8_t* binary, ImageFormat format, Image& outImage);
    static bool load(const std::string& file, ImageFormat format, Image& outImage);
    static void destroy();

private:
    ImageIO() = delete;
    ~ImageIO() = delete;
    static void loadImpl(void* vdib, Image& outImage);
    static int toFreeImageFormat(ImageFormat format);
    static bool s_initialized;
};
}