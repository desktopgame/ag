#include <ag/graphics/FontSprite.hpp>
namespace ag {
FontSprite::FontSprite(const std::shared_ptr<Texture>& texture,
    FontMetrics metrics)
    : texture(texture)
    , metrics(metrics)
{
}
}
