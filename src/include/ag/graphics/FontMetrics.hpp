#pragma once
#include <ag/native/glm.hpp>

namespace ag {
class FontMetrics {
public:
    explicit FontMetrics(glm::ivec2 size, glm::ivec2 bearing,
        glm::ivec2 advance);

    const glm::ivec2 size;
    const glm::ivec2 bearing;
    const glm::ivec2 advance;
};
}
