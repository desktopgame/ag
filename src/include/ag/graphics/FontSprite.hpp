#pragma once
#include <ag/graphics/FontMetrics.hpp>
#include <memory>

namespace ag {
class ITexture;
class FontSprite {
public:
    using Reference = std::weak_ptr<FontSprite>;
    using Instance = std::shared_ptr<FontSprite>;
    explicit FontSprite(const std::shared_ptr<ITexture>& texture,
        FontMetrics metrics);
    const std::shared_ptr<ITexture> texture;
    const FontMetrics metrics;

private:
};
}