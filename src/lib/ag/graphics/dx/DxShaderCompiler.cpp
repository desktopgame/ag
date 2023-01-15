#ifdef AG_DIRECT_X
#include <ag/graphics/dx/DxShaderCompiler.hpp>

namespace ag {

std::shared_ptr<IShader> DxShaderCompiler::compileFromPartedSource(const std::string& vSource, const std::string& fSource)
{
    return nullptr;
}
bool DxShaderCompiler::isCompilableFromPartedSource() const
{
    return false;
}

std::shared_ptr<IShader> DxShaderCompiler::compileFromSingleSource(const std::string& source)
{
    return nullptr;
}
bool DxShaderCompiler::isCompilableFromSingleSource() const
{
    return false;
}

std::shared_ptr<IShader> DxShaderCompiler::compileFromSingleFile(const std::string& file)
{
    return nullptr;
}
bool DxShaderCompiler::isCompilableFromSingleFile() const
{
    return false;
}
}
#endif