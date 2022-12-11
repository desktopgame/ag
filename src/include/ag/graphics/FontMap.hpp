#pragma once
#include <ag/ImageIO.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace ag {
class Font;
class FontSprite;
class FontInstance;
class Texture;
class FontMap {
public:
    explicit FontMap(const std::shared_ptr<Font>& font);
    std::vector<std::shared_ptr<FontSprite>> load(
        int size, const std::u16string& str);
    std::shared_ptr<FontSprite> load(int size, unsigned long charcode);
    bool isOccurredError() const;

private:
    static void fontToPixel(const std::shared_ptr<FontInstance>& instance, std::vector<Pixel>& outPixels);
    class Container;
    std::shared_ptr<Font> m_font;
    std::vector<std::shared_ptr<Container>> m_containerVec;
};
}