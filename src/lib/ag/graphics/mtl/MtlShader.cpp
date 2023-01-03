#ifdef AG_METAL
#include <ag/Engine.hpp>
#include <ag/graphics/IGraphicsDevice.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/mtl/MtlBuffer.hpp>
#include <ag/graphics/mtl/MtlShader.hpp>
#include <ag/native/glm.hpp>

namespace ag {

MtlShader::MtlShader(MTL::Library* lib, MTL::Function* vFunc, MTL::Function* fFunc, MtlUniformManager::Instance uniformManager)
    : m_lib(lib)
    , m_vFunc(vFunc)
    , m_fFunc(fFunc)
    , m_transformMatrixBuf(nullptr)
    , m_textureBuf(nullptr)
    , m_color1Buf(nullptr)
    , m_color2Buf(nullptr)
    , m_uniformManager(uniformManager)
{
}
MtlShader::~MtlShader()
{
    m_lib->release();
    m_vFunc->release();
    m_fFunc->release();
}
void MtlShader::apply(const std::shared_ptr<ShaderParameter>& parameter)
{
    auto driver = Engine::getInstance()->getGraphicsDriver();
    auto device = driver->getGraphicsDevice();
    // matrix buffer
    if (!m_transformMatrixBuf) {
        m_transformMatrixBuf = m_uniformManager->rentTransformBuffer();
    }
    const glm::mat4 t = parameter->getTransform();
    const glm::vec4& v0 = glm::row(t, 0);
    const glm::vec4& v1 = glm::row(t, 1);
    const glm::vec4& v2 = glm::row(t, 2);
    const glm::vec4& v3 = glm::row(t, 3);
    simd::float4x4 simdMat = simd_matrix_from_rows((simd::float4) { v0.x, v0.y, v0.z, v0.w },
        (simd::float4) { v1.x, v1.y, v1.z, v1.w },
        (simd::float4) { v2.x, v2.y, v2.z, v2.w },
        (simd::float4) { v3.x, v3.y, v3.z, v3.w });
    m_transformMatrixBuf->update(&simdMat);
    // color buffer
    if (!m_color1Buf) {
        m_color1Buf = m_uniformManager->rentColorBuffer();
    }
    m_color1Buf->update(glm::value_ptr(parameter->getColor1()));
}
void MtlShader::attachFunction(MTL::RenderPipelineDescriptor* desc)
{
    desc->setVertexFunction(m_vFunc);
    desc->setFragmentFunction(m_fFunc);
}

void MtlShader::attachTransform(MTL::RenderCommandEncoder* encoder, int offset, int index)
{
    auto mtlTransformMatrixBuf = std::static_pointer_cast<MtlBuffer>(m_transformMatrixBuf);
    mtlTransformMatrixBuf->attachAsVertex(encoder, offset, index);
}
void MtlShader::attachColor1(MTL::RenderCommandEncoder* encoder, int offset, int index)
{
    auto mtlColor1Buf = std::static_pointer_cast<MtlBuffer>(m_color1Buf);
    mtlColor1Buf->attachAsFragment(encoder, offset, index);
}

void MtlShader::detach()
{
    m_transformMatrixBuf = nullptr;
    m_color1Buf = nullptr;
    m_color2Buf = nullptr;
}
}
#endif