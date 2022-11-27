#include <ag/graphics/mtl/MtlShader.hpp>
#ifdef AG_METAL

namespace ag {

MtlShader::MtlShader(MTL::Library* lib, MTL::Function* vFunc, MTL::Function* fFunc)
    : m_lib(lib)
    , m_vFunc(vFunc)
    , m_fFunc(fFunc)
{
    m_lib->retain();
    m_vFunc->retain();
    m_fFunc->retain();
}
MtlShader::~MtlShader()
{
    m_lib->release();
    m_vFunc->release();
    m_fFunc->release();
}
void MtlShader::apply(const std::shared_ptr<ShaderParameter>& parameter) { }
void MtlShader::attach(MTL::RenderPipelineDescriptor* desc)
{
    desc->setVertexFunction(m_vFunc);
    desc->setFragmentFunction(m_fFunc);
}
}
#endif