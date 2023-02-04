#ifdef AG_DIRECT_X
#include <ag/graphics/dx/DxShader.hpp>
#include <ag/graphics/dx/DxShaderCompiler.hpp>
#include <ag/native/dx.hpp>

namespace ag {

std::shared_ptr<IShader> DxShaderCompiler::compileFromPartedSource(const std::string& vSource, const std::string& fSource)
{
    ID3DBlob* vsBlob = nullptr;
    ID3DBlob* psBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;
    // make flags
    UINT flags = 0;
#ifdef AG_DEBUG
    flags = D3DCOMPILE_DEBUG;
#endif
    flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
    // compile shader
    if (FAILED(D3DCompile(
            vSource.c_str(),
            vSource.size(),
            "VertexShader",
            nullptr,
            D3D_COMPILE_STANDARD_FILE_INCLUDE,
            "BasicVS",
            "vs_5_0",
            flags,
            0,
            &vsBlob,
            &errorBlob))) {
        return nullptr;
    }

    if (FAILED(D3DCompile(
            fSource.c_str(),
            fSource.size(),
            "PixelShader",
            nullptr,
            D3D_COMPILE_STANDARD_FILE_INCLUDE,
            "BasicPS",
            "ps_5_0",
            flags,
            0,
            &vsBlob,
            &errorBlob))) {
        return nullptr;
    }
    return std::make_shared<DxShader>(vsBlob, psBlob);
}
bool DxShaderCompiler::isCompilableFromPartedSource() const
{
    return true;
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