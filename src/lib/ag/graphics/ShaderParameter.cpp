#include <ag/graphics/ShaderParameter.hpp>

namespace ag {
ShaderParameter::ShaderParameter()
    : m_transform()
    , m_texture()
    , m_useTexture()
    , m_color()
    , m_useColor()
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

void ShaderParameter::setColor(const glm::vec4& color)
{
    m_color = color;
    m_useColor = true;
}
glm::vec4 ShaderParameter::getColor() const { return m_color; }
bool ShaderParameter::useColor() const { return m_useColor; }
}