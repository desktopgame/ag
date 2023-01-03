#include <ag/graphics/Material.hpp>

namespace ag {
Material::Material()
    : ambient()
    , diffuse()
    , specular()
    , emission()
    , shininess()
    , texture(nullptr)
    , texCoordIndex(-1)
{
}
}