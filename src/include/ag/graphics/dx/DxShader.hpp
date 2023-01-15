#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/IShader.hpp>

namespace ag {
class DxShader : public IShader {
public:
    explicit DxShader() = default;
    void apply(const std::shared_ptr<ShaderParameter>& parameter) override;

private:
};
}
#endif