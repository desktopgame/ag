#pragma once
#ifdef AG_METAL
#include <ag/graphics/IBuffer.hpp>
#include <ag/graphics/IShader.hpp>
#include <ag/graphics/mtl/MtlBufferPool.hpp>
#include <ag/graphics/mtl/MtlUniformManager.hpp>
#include <ag/native/glfw.hpp>
#include <ag/native/metal.hpp>

namespace ag {
class MtlShader : public IShader {
public:
    explicit MtlShader(MTL::Library* lib, MTL::Function* vFunc, MTL::Function* fFunc, MtlUniformManager::Instance uniformManager);
    ~MtlShader();
    void apply(const std::shared_ptr<ShaderParameter>& parameter);
    void attachFunction(MTL::RenderPipelineDescriptor* desc);
    void attachTransform(MTL::RenderCommandEncoder* encoder, int offset, int index);
    void attachColor(MTL::RenderCommandEncoder* encoder, int offset, int index);
    void detach();

private:
    MTL::Library* m_lib;
    MTL::Function* m_vFunc;
    MTL::Function* m_fFunc;
    IBuffer::Instance m_transformMatrixBuf;
    IBuffer::Instance m_textureBuf;
    IBuffer::Instance m_colorBuf;
    MtlUniformManager::Instance m_uniformManager;
};
}
#endif