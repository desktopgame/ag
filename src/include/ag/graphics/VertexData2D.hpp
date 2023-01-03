#pragma once
#include <ag/native/glm.hpp>

namespace ag {
struct VertexData2D {
    glm::vec2 position;
    glm::vec2 texcoord;

    explicit VertexData2D();
    VertexData2D(const glm::vec2& position, const glm::vec2& texcoord);
};
}