#pragma once
#include <ag/graphics/IShader.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
class MtlShader : public IShader {
public:
    explicit MtlShader();
    ~MtlShader();
    void apply(const std::shared_ptr<ShaderParameter>& parameter) override;

private:
};
}