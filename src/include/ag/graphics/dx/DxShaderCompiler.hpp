#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/IShaderCompiler.hpp>

namespace ag {
class DxShaderCompiler : public IShaderCompiler {
public:
    explicit DxShaderCompiler() = default;

    std::shared_ptr<IShader> compileFromPartedSource(const std::string& vSource, const std::string& fSource) override;
    bool isCompilableFromPartedSource() const override;

    std::shared_ptr<IShader> compileFromSingleSource(const std::string& source) override;
    bool isCompilableFromSingleSource() const override;

    std::shared_ptr<IShader> compileFromSingleFile(const std::string& file) override;
    bool isCompilableFromSingleFile() const override;

private:
};
}
#endif