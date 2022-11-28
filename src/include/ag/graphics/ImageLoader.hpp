#pragma once
#include <ag/ImageIO.hpp>
#include <string>
#include <unordered_map>

namespace ag {
class ImageLoader {
public:
    static bool load(const std::string& file, Image& img);

private:
    ImageLoader() = delete;
    ~ImageLoader() = delete;
    static std::unordered_map<std::string, Image> s_imageMap;
};
}