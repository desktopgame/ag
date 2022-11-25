#include <ag/graphics/ShaderParameter.hpp>

namespace ag {
ShaderParameter::ShaderParameter()
    : m_transform()
    , m_texture()
    , m_useTexture()
    , m_color1()
    , m_useColor1()
    , m_color2()
    , m_useColor2()
{
}

void ShaderParameter::setTransform(const glm::mat4& transform)
{
    m_transform = transform;
}
glm::mat4 ShaderParameter::getTransform() const
{
    return m_transform;
}

void ShaderParameter::setTexture(const std::shared_ptr<ITexture>& texture)
{
    m_texture = texture;
    m_useTexture = true;
}
std::shared_ptr<ITexture> ShaderParameter::getTexture() { return m_texture; }
bool ShaderParameter::useTexture() const { return m_useTexture; }

void ShaderParameter::setColor1(const glm::vec4& color1)
{
    m_color1 = color1;
    m_useColor1 = true;
}
glm::vec4 ShaderParameter::getColor1() const { return m_color1; }
bool ShaderParameter::useColor1() const { return m_useColor1; }

void ShaderParameter::setColor2(const glm::vec4& color2)
{
    m_color2 = color2;
    m_useColor2 = true;
}
glm::vec4 ShaderParameter::getColor2() const { return m_color2; }
bool ShaderParameter::useColor2() const { return m_useColor2; }
}