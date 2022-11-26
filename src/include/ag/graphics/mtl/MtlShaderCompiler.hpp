#pragma once
#include <ag/graphics/IShaderCompiler.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
class MtlShaderCompiler : public IShaderCompiler {
public:
    MtlShaderCompiler() = default;
    ~MtlShaderCompiler() = default;

    std::shared_ptr<IShader> compileFromSource(const std::string& vSource, const std::string& fSource) override;
    bool isCompilableFromSource() const override;

    std::shared_ptr<IShader> compileFromSingleFile(const std::string& file) override;
    bool isCompilableFromSingleFile() const override;

private:
};
}