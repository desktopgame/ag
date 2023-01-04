#pragma once
#include <ag/graphics/IShader.hpp>
#include <ag/graphics/Material.hpp>
#include <ag/graphics/RenderingContext.hpp>
#include <string>

namespace ag {
class Mesh {
public:
    using Instance = std::shared_ptr<Mesh>;
    explicit Mesh(const std::string& name, int primCount);
    void updateVertex(const glm::vec3* data, int len);
    void updateVertex(const VertexData3D* data, int len);
    void updateIndex(const unsigned int* data, int len);
    void draw(const std::shared_ptr<IShader>& shader, const glm::mat4& transform);
    std::shared_ptr<Material> getMaterial() const;

private:
    std::string m_name;
    int m_primCount;
    std::shared_ptr<Material> m_material;
    RenderingContext::Instance m_renderingContext;
};
}