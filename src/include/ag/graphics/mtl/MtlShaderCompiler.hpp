#pragma once
#ifdef AG_METAL
#include <ag/graphics/IShaderCompiler.hpp>
#include <ag/native/glfw.hpp>
#include <ag/native/metal.hpp>

namespace ag {
class MtlShaderCompiler : public IShaderCompiler {
public:
    MtlShaderCompiler(MTL::Device* device, MtlBufferPool::Instance matrixPool, MtlBufferPool::Instance colorPool);
    ~MtlShaderCompiler();

    std::shared_ptr<IShader> compileFromPartedSource(const std::string& vSource, const std::string& fSource) override;
    bool isCompilableFromPartedSource() const override;

    std::shared_ptr<IShader> compileFromSingleSource(const std::string& source) override;
    bool isCompilableFromSingleSource() const override;

    std::shared_ptr<IShader> compileFromSingleFile(const std::string& file) override;
    bool isCompilableFromSingleFile() const override;

private:
    MTL::Device* m_device;
    MtlBufferPool::Instance m_matrixPool;
    MtlBufferPool::Instance m_colorPool;
};
}
#endif