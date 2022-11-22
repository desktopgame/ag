#pragma once
#include <ag/native/glm.hpp>
#include <memory>

namespace ag {
class ITexture;
class IShaderParameter {
    using Instance = std::shared_ptr<IShaderParameter>;
    IShaderParameter() = default;
    virtual ~IShaderParameter() = default;

    virtual void setTransform(const glm::mat4& transform) = 0;
    virtual glm::mat4 getTransform() const = 0;

    virtual void setTexture(const std::shared_ptr<ITexture>& texture) = 0;
    virtual std::shared_ptr<ITexture> getTexture() = 0;
    virtual bool useTexture() const = 0;

    virtual void setColor1(const glm::vec4& color1) = 0;
    virtual glm::vec4 getColor1() const = 0;
    virtual bool useColor1() const = 0;

    virtual void setColor2(const glm::vec4& color2) = 0;
    virtual glm::vec4 getColor2() const = 0;
    virtual bool useColor2() const = 0;
};
}