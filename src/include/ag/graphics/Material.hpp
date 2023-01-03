#pragma once
#include <ag/graphics/ITexture.hpp>
#include <memory>

namespace ag {
class Material {
public:
    using Instance = std::shared_ptr<Material>;
    explicit Material();
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    glm::vec4 emission;
    float shininess;
    std::shared_ptr<ITexture> texture;
    int texCoordIndex;

private:
};
}