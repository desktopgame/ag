#pragma once
#include <ag/graphics/PrimitiveType.hpp>
#include <ag/graphics/ShaderParameter.hpp>
#include <ag/graphics/VertexData2D.hpp>
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

    virtual void draw(const std::shared_ptr<IShader>& shader, PrimitiveType primitiveType, int primCount) = 0;

    void updateVertex(const glm::vec2* data, int len);
    void updateVertex(const VertexData2D* data, int len);
    void updateIndex(const unsigned int* data, int len);

    size_t getVertexLength() const;
    size_t getIndexLength() const;
    std::shared_ptr<ShaderParameter> getParameter() const;

protected:
    std::shared_ptr<ShaderParameter> m_parameter;
    std::shared_ptr<IBuffer> m_vertex;
    std::shared_ptr<IBuffer> m_index;
    size_t m_vertexLength;
    size_t m_indexLength;
    bool m_isUsingTexCoord;
};
}