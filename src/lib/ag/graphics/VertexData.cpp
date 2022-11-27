#include <ag/graphics/VertexData.hpp>

namespace ag {
VertexData::VertexData()
    : position()
    , texcoord()
{
}
VertexData::VertexData(const glm::vec2& position, const glm::vec2& texcoord)
    : position(position)
    , texcoord(texcoord)
{
}
}