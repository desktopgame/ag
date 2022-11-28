#ifdef AG_METAL
#include <ag/graphics/mtl/MtlShader.hpp>
#include <ag/graphics/mtl/MtlShaderCompiler.hpp>

namespace ag {

MtlShaderCompiler::MtlShaderCompiler(MTL::Device* device)
    : m_device(device)
{
    m_device->retain();
}
MtlShaderCompiler::~MtlShaderCompiler()
{
    m_device->release();
}

std::shared_ptr<IShader> MtlShaderCompiler::compileFromPartedSource(const std::string& vSource, const std::string& fSource) { return nullptr; }
bool MtlShaderCompiler::isCompilableFromPartedSource() const { return false; }

std::shared_ptr<IShader> MtlShaderCompiler::compileFromSingleSource(const std::string& source)
{
    NS::Error* err = nullptr;
    NS::String* nsSource = NS::String::alloc()->init(source.c_str(), NS::StringEncoding::UTF8StringEncoding);
    NS::String* vFuncName = NS::String::alloc()->init("vertexShader", NS::StringEncoding::UTF8StringEncoding);
    NS::String* fFuncName = NS::String::alloc()->init("fragmentShader", NS::StringEncoding::UTF8StringEncoding);
    MTL::Library* lib = m_device->newLibrary(nsSource, MTL::CompileOptions::alloc()->init(), &err);
    if (err) {
        throw std::logic_error(err->description()->cString(NS::StringEncoding::UTF8StringEncoding));
    }
    MTL::Function* vFunc = lib->newFunction(vFuncName);
    MTL::Function* fFunc = lib->newFunction(fFuncName);
    nsSource->release();
    vFuncName->release();
    fFuncName->release();
    return std::make_shared<MtlShader>(lib, vFunc, fFunc);
}
bool MtlShaderCompiler::isCompilableFromSingleSource() const { return true; }

std::shared_ptr<IShader> MtlShaderCompiler::compileFromSingleFile(const std::string& file) { return nullptr; }
bool MtlShaderCompiler::isCompilableFromSingleFile() const { return true; }
}
#endif