#pragma once
#include <ag/native/glm.hpp>

namespace ag {
struct VertexData3D {
    glm::vec3 position;
    glm::vec2 texcoord;

    explicit VertexData3D();
    VertexData3D(const glm::vec3& position, const glm::vec2& texcoord);
};
}