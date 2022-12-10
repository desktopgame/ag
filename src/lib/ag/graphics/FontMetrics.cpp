#include <ag/graphics/FontMetrics.hpp>

namespace ag {
FontMetrics::FontMetrics(glm::ivec2 size, glm::ivec2 bearing,
    glm::ivec2 advance)
    : size(size)
    , bearing(bearing)
    , advance(advance)
{
}
}
