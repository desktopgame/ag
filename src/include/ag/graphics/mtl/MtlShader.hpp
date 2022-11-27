#pragma once
#ifdef AG_METAL
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

private:
    MTL::Library* m_lib;
    MTL::Function* m_vFunc;
    MTL::Function* m_fFunc;
};
}
#endif