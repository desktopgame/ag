#pragma once
#include <ag/native/glm.hpp>
#include <memory>

namespace ag {
class ITexture;
class ShaderParameter {
public:
    using Instance = std::shared_ptr<ShaderParameter>;
    ShaderParameter();
    virtual ~ShaderParameter() = default;

    void setTransform(const glm::mat4& transform);
    glm::mat4 getTransform() const;

    void setTexture(const std::shared_ptr<ITexture>& texture);
    std::shared_ptr<ITexture> getTexture();
    bool useTexture() const;

    void setColor1(const glm::vec4& color1);
    glm::vec4 getColor1() const;
    bool useColor1() const;

    void setColor2(const glm::vec4& color2);
    glm::vec4 getColor2() const;
    bool useColor2() const;

private:
    glm::mat4 m_transform;
    std::shared_ptr<ITexture> m_texture;
    bool m_useTexture;

    glm::vec4 m_color1;
    bool m_useColor1;

    glm::vec4 m_color2;
    bool m_useColor2;
};
}