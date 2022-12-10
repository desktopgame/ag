#pragma once
#include <ag/graphics/FontMetrics.hpp>
#include <memory>

namespace ag {
class Texture;
class FontSprite {
public:
    using Reference = std::weak_ptr<FontSprite>;
    using Instance = std::shared_ptr<FontSprite>;
    explicit FontSprite(const std::shared_ptr<Texture>& texture,
        FontMetrics metrics);
    const std::shared_ptr<Texture> texture;
    const FontMetrics metrics;

private:
};
}