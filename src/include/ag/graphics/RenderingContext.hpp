#pragma once
#include <ag/graphics/ShaderParameter.hpp>
#include <ag/native/glm.hpp>
#include <memory>
#include <vector>

namespace ag {
class IBuffer;
class IShader;
class RenderingContext {
public:
    using Instance = std::shared_ptr<RenderingContext>;
    explicit RenderingContext();
    virtual ~RenderingContext() = default;

    virtual void setup(const std::shared_ptr<IShader>& shader) = 0;
    virtual void teardown(const std::shared_ptr<IShader>& shader) = 0;

    void updateVertex(const std::vector<glm::vec3>& data);
    void updateIndex(const std::vector<unsigned short>& data);

    size_t getVertexLength() const;
    size_t getIndexLength() const;
    std::shared_ptr<ShaderParameter> getParameter() const;

protected:
    std::shared_ptr<ShaderParameter> m_parameter;
    std::shared_ptr<IBuffer> m_vertex;
    std::shared_ptr<IBuffer> m_index;
    size_t m_vertexLength;
    size_t m_indexLength;
};
}