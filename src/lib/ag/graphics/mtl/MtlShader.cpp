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
    , m_colorBuf(nullptr)
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
    m_transformMatrixBuf->update(glm::value_ptr(parameter->getTransform()));
    // color buffer
    if (!m_colorBuf) {
        m_colorBuf = m_uniformManager->rentColorBuffer();
    }
    m_colorBuf->update(glm::value_ptr(parameter->getColor1()));
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
void MtlShader::attachColor(MTL::RenderCommandEncoder* encoder, int offset, int index)
{
    auto mtlColorBuf = std::static_pointer_cast<MtlBuffer>(m_colorBuf);
    mtlColorBuf->attachAsFragment(encoder, offset, index);
}

void MtlShader::detach()
{
    m_transformMatrixBuf = nullptr;
    m_colorBuf = nullptr;
}
}
#endif