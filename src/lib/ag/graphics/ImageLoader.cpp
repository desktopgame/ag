#include <ag/graphics/ImageLoader.hpp>

namespace ag {
std::unordered_map<std::string, Image> ImageLoader::s_imageMap;

bool ImageLoader::load(const std::string& file, Image& img)
{
    bool status = false;
    if (!s_imageMap.count(file)) {
        Image dst;
        if (ImageIO::load(file, ag::ImageFormat::PNG, dst)) {
            s_imageMap.insert_or_assign(file, dst);
        }
    }
    if (s_imageMap.count(file)) {
        img = s_imageMap.at(file);
        status = true;
    }
    return status;
}
}