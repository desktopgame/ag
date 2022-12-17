#include <ag/ui/Font.hpp>

namespace agui {
Font::Font(std::shared_ptr<ag::FontMap> map, int size)
    : map(map)
    , size(size)
{
}
Font::Font(const Font& font)
    : map(font.map)
    , size(font.size)
{
}
}