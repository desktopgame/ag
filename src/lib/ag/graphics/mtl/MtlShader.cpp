#ifdef AG_METAL
#include <ag/Engine.hpp>
#include <ag/graphics/IGraphicsDevice.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/mtl/MtlBuffer.hpp>
#include <ag/graphics/mtl/MtlShader.hpp>

namespace ag {

MtlShader::MtlShader(MtlBufferPool::Instance matrixPool, MtlBufferPool::Instance colorPool, MTL::Library* lib, MTL::Function* vFunc, MTL::Function* fFunc)
    : m_matrixPool(matrixPool)
    , m_colorPool(colorPool)
    , m_lib(lib)
    , m_vFunc(vFunc)
    , m_fFunc(fFunc)
    , m_transformMatrixBuf(nullptr)
    , m_textureBuf(nullptr)
    , m_color1Buf(nullptr)
    , m_color2Buf(nullptr)
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
void MtlShader::apply(const std::shared_ptr<ShaderParameter>& parameter)
{
    auto driver = Engine::getInstance()->getGraphicsDriver();
    auto device = driver->getGraphicsDevice();
    // matrix buffer
    if (!m_transformMatrixBuf) {
        // m_transformMatrixBuf = device->newVertexBuffer();
        // m_transformMatrixBuf->allocate(sizeof(glm::mat4));
        m_transformMatrixBuf = m_matrixPool->rent();
    }
    m_transformMatrixBuf->update(glm::value_ptr(parameter->getTransform()));
    // color buffer
    if (!m_color1Buf) {
        // m_color1Buf = device->newVertexBuffer();
        // m_color1Buf->allocate(sizeof(glm::vec4));
        m_color1Buf = m_colorPool->rent();
    }
    m_color1Buf->update(glm::value_ptr(parameter->getColor1()));
}
void MtlShader::attach(MTL::RenderPipelineDescriptor* desc)
{
    desc->setVertexFunction(m_vFunc);
    desc->setFragmentFunction(m_fFunc);
}

void MtlShader::useTransform(MTL::RenderCommandEncoder* encoder, int offset, int index)
{
    auto mtlTransformMatrixBuf = std::static_pointer_cast<MtlBuffer>(m_transformMatrixBuf);
    mtlTransformMatrixBuf->attachAsVertex(encoder, offset, index);
}
void MtlShader::useColor1(MTL::RenderCommandEncoder* encoder, int offset, int index)
{
    auto mtlColor1Buf = std::static_pointer_cast<MtlBuffer>(m_color1Buf);
    mtlColor1Buf->attachAsFragment(encoder, offset, index);
}

void MtlShader::release()
{
    m_transformMatrixBuf = nullptr;
    m_color1Buf = nullptr;
    m_color2Buf = nullptr;
}
}
#endif