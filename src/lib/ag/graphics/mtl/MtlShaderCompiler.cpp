#include <ag/graphics/mtl/MtlShaderCompiler.hpp>
#ifdef AG_METAL

namespace ag {

std::shared_ptr<IShader> MtlShaderCompiler::compileFromPartedSource(const std::string& vSource, const std::string& fSource) { return nullptr; }
bool MtlShaderCompiler::isCompilableFromPartedSource() const { return true; }
std::shared_ptr<IShader> MtlShaderCompiler::compileFromSingleFile(const std::string& file) { return nullptr; }
bool MtlShaderCompiler::isCompilableFromSingleFile() const { return true; }
}
#endif