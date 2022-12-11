#include <ag/Engine.hpp>
#include <ag/graphics/Font.hpp>
#include <ag/graphics/FontMap.hpp>
#include <ag/graphics/FontSprite.hpp>
#include <ag/graphics/IGraphicsDevice.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/ITexture.hpp>
#include <algorithm>
namespace ag {
// Container
class FontMap::Container {
public:
    explicit Container(int size)
        : size(size)
        , textureMap()
    {
    }
    int size;
    std::unordered_map<char, std::shared_ptr<FontSprite>> textureMap;
};
// FontMap
FontMap::FontMap(const std::shared_ptr<Font>& font)
    : m_font(font)
    , m_containerVec()
{
}
std::shared_ptr<FontSprite> FontMap::load(int size, unsigned long charcode)
{
    auto iter = std::find_if(m_containerVec.begin(), m_containerVec.end(),
        [size](std::shared_ptr<Container> c) -> bool {
            return size == c->size;
        });
    if (iter == m_containerVec.end()) {
        auto c = std::make_shared<Container>(size);
        m_containerVec.emplace_back(c);
        return load(size, charcode);
    }
    auto c = *iter;
    if (c->textureMap.count(charcode)) {
        return c->textureMap.at(charcode);
    }
    m_font->load(size, charcode);
    auto fontInstance = m_font->getCurrentInstance();
    std::vector<Pixel> pixels;
    fontToPixel(fontInstance, pixels);
    auto texture = Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice()->newTexture(
        fontInstance->metrics.size.x,
        fontInstance->metrics.size.y,
        &pixels.front().r);
    auto fontSprite = std::make_shared<FontSprite>(texture, fontInstance->metrics);
    c->textureMap[charcode] = fontSprite;
    return fontSprite;
}
std::vector<std::shared_ptr<FontSprite>> FontMap::load(
    int size, const std::u16string& str)
{
    std::vector<std::shared_ptr<FontSprite>> v;
    for (char16_t c : str) {
        v.emplace_back(load(size, c));
    }
    return v;
}
bool FontMap::isOccurredError() const { return m_font->isOccurredError(); }
// private
void FontMap::fontToPixel(const std::shared_ptr<FontInstance>& instance, std::vector<Pixel>& outPixels)
{
    int w = instance->metrics.size.x;
    int h = instance->metrics.size.y;
    for (int i = 0; i < w * h; i++) {
        Pixel p;
        p.a = instance->data[i];
        outPixels.push_back(p);
    }
}
}