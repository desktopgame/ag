#include <ag/graphics/mtl/MtlShaderCompiler.hpp>

namespace ag {

std::shared_ptr<IShader> MtlShaderCompiler::compileFromSource(const std::string& vSource, const std::string& fSource) { return nullptr; }
bool MtlShaderCompiler::isCompilableFromSource() const { return true; }
std::shared_ptr<IShader> MtlShaderCompiler::compileFromSingleFile(const std::string& file) { return nullptr; }
bool MtlShaderCompiler::isCompilableFromSingleFile() const { return true; }
}