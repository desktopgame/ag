#pragma once
#include <ag/native/glm.hpp>
#include <memory>
#include <vector>

namespace ag {
class IBuffer;
class IShader;
class IShaderParameter;
class RenderingContext {
public:
    using Instance = std::shared_ptr<RenderingContext>;
    explicit RenderingContext();
    virtual ~RenderingContext() = default;

    virtual void setup(const std::shared_ptr<IShader>& shader) = 0;
    virtual void teardown() = 0;

    void updateVertex(const std::vector<glm::vec3>& data);
    void updateIndex(const std::vector<unsigned short>& data);

protected:
    std::shared_ptr<IShaderParameter> m_parameter;
    std::shared_ptr<IBuffer> m_vertex;
    std::shared_ptr<IBuffer> m_index;
    size_t m_indexLength;
};
}