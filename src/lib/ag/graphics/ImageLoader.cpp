#include <ag/graphics/ImageLoader.hpp>

namespace ag {
std::unordered_map<std::string, Image> ImageLoader::s_imageMap;

bool ImageLoader::load(const std::string& file, Image& img)
{
    if (s_imageMap.count(file)) {
        img = s_imageMap.at(file);
        return true;
    } else {
        return ImageIO::load(file, ag::ImageFormat::PNG, img);
    }
}
}