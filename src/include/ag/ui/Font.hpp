#pragma once
#include <ag/graphics/FontMap.hpp>

namespace agui {
class Font {
public:
    explicit Font(std::shared_ptr<ag::FontMap> map, int size);
    Font(const Font& font);
    std::shared_ptr<ag::FontMap> map;
    int size;

private:
};
}