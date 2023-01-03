#include <ag/graphics/VertexData2D.hpp>

namespace ag {
VertexData2D::VertexData2D()
    : position()
    , texcoord()
{
}
VertexData2D::VertexData2D(const glm::vec2& position, const glm::vec2& texcoord)
    : position(position)
    , texcoord(texcoord)
{
}
}