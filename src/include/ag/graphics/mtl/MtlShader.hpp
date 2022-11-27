#pragma once
#ifdef AG_METAL
#include <ag/graphics/IBuffer.hpp>
#include <ag/graphics/IShader.hpp>
#include <ag/native/glfw.hpp>
#include <ag/native/metal.hpp>

namespace ag {
class MtlShader : public IShader {
public:
    explicit MtlShader(MTL::Library* lib, MTL::Function* vFunc, MTL::Function* fFunc);
    ~MtlShader();
    void apply(const std::shared_ptr<ShaderParameter>& parameter) override;
    void attach(MTL::RenderPipelineDescriptor* desc);
    void useTransform(MTL::RenderCommandEncoder* encoder, int offset, int index);
    void useColor1(MTL::RenderCommandEncoder* encoder, int offset, int index);

private:
    MTL::Library* m_lib;
    MTL::Function* m_vFunc;
    MTL::Function* m_fFunc;
    IBuffer::Instance m_transformMatrixBuf;
    IBuffer::Instance m_textureBuf;
    IBuffer::Instance m_color1Buf;
    IBuffer::Instance m_color2Buf;
};
}
#endif