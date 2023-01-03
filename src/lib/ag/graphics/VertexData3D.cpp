#include <ag/graphics/VertexData3D.hpp>

namespace ag {
VertexData3D::VertexData3D()
    : position()
    , texcoord()
{
}
VertexData3D::VertexData3D(const glm::vec3& position, const glm::vec2& texcoord)
    : position(position)
    , texcoord(texcoord)
{
}
}