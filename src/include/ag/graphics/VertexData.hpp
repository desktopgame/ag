#pragma once
#include <ag/native/glm.hpp>

namespace ag {
struct VertexData {
    glm::vec2 position;
    glm::vec2 texcoord;

    explicit VertexData();
    VertexData(const glm::vec2& position, const glm::vec2& texcoord);
};
}