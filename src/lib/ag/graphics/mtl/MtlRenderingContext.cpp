#ifdef AG_METAL
#include <ag/Engine.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/ShaderParameter.hpp>
#include <ag/graphics/mtl/MtlBuffer.hpp>
#include <ag/graphics/mtl/MtlGraphicsDevice.hpp>
#include <ag/graphics/mtl/MtlRenderFunction.hpp>
#include <ag/graphics/mtl/MtlRenderingContext.hpp>
#include <ag/graphics/mtl/MtlShader.hpp>
#include <ag/graphics/mtl/MtlTexture.hpp>

namespace ag {
MtlRenderingContext::MtlRenderingContext()
    : m_renderPipelineState(nullptr)
{
}
MtlRenderingContext::~MtlRenderingContext()
{
    if (m_renderPipelineState) {
        m_renderPipelineState->release();
    }
}
void MtlRenderingContext::draw(const std::shared_ptr<IShader>& shader, PrimitiveType primitiveType, int primCount)
{
    auto mtlIndex = std::static_pointer_cast<MtlBuffer>(m_index);
    auto mtlFunc = std::static_pointer_cast<MtlRenderFunction>(Engine::getInstance()->getGraphicsDriver()->getRenderFunction());
    auto encoder = mtlFunc->getRenderCommandEncoder();
    beginBuffer(shader);
    // draw
    if (m_indexLength > 0) {
        mtlIndex->drawWithIndex(encoder, convPrimitiveType(primitiveType));
    } else {
        NS::UInteger nsOffs = static_cast<NS::UInteger>(0);
        NS::UInteger nsPrimCount = static_cast<NS::UInteger>(primCount);
        encoder->drawPrimitives(convPrimitiveType(primitiveType), nsOffs, nsPrimCount);
    }
    endBuffer(shader);
}
// private
void MtlRenderingContext::beginBuffer(const std::shared_ptr<IShader>& shader)
{
    auto mtlShader = std::static_pointer_cast<MtlShader>(shader);
    auto mtlFunc = std::static_pointer_cast<MtlRenderFunction>(Engine::getInstance()->getGraphicsDriver()->getRenderFunction());
    // setup shader
    createRenderPipelineState(shader);
    shader->apply(m_parameter);
    // get encoder
    auto encoder = mtlFunc->getRenderCommandEncoder();
    // update vertex, uniform
    auto mtlVertex = std::static_pointer_cast<MtlBuffer>(m_vertex);
    auto mtlIndex = std::static_pointer_cast<MtlBuffer>(m_index);
    encoder->setRenderPipelineState(m_renderPipelineState);
    mtlVertex->attachAsVertex(encoder, 0, 0);
    mtlShader->attachTransform(encoder, 0, 1);
    if (m_parameter->useColor1()) {
        mtlShader->attachColor1(encoder, 0, 2);
    }
    if (m_parameter->useTexture()) {
        auto mtlTexture = std::static_pointer_cast<MtlTexture>(m_parameter->getTexture());
        mtlTexture->attach(encoder, 10);
    }
}
void MtlRenderingContext::endBuffer(const std::shared_ptr<IShader>& shader)
{
    auto mtlShader = std::static_pointer_cast<MtlShader>(shader);
    mtlShader->release();
}
void MtlRenderingContext::createRenderPipelineState(const std::shared_ptr<IShader>& shader)
{
    auto mtlShader = std::static_pointer_cast<MtlShader>(shader);
    auto mtlDevice = std::static_pointer_cast<MtlGraphicsDevice>(Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice());
    if (!m_renderPipelineState) {
        MTL::RenderPipelineDescriptor* desc = MTL::RenderPipelineDescriptor::alloc()->init();
        MTL::RenderPipelineColorAttachmentDescriptor* colorDesc = desc->colorAttachments()->object(0);
        mtlShader->attachFunction(desc);
        colorDesc->setPixelFormat(
            MTL::PixelFormatBGRA8Unorm);
        colorDesc->setBlendingEnabled(true);
        colorDesc->setRgbBlendOperation(MTL::BlendOperation::BlendOperationAdd);
        colorDesc->setAlphaBlendOperation(MTL::BlendOperation::BlendOperationAdd);
        colorDesc->setSourceRGBBlendFactor(MTL::BlendFactor::BlendFactorSourceAlpha);
        colorDesc->setSourceAlphaBlendFactor(MTL::BlendFactor::BlendFactorSourceAlpha);
        colorDesc->setDestinationRGBBlendFactor(MTL::BlendFactor::BlendFactorOneMinusSourceAlpha);
        colorDesc->setDestinationAlphaBlendFactor(MTL::BlendFactor::BlendFactorOneMinusSourceAlpha);
        desc->setDepthAttachmentPixelFormat(MTL::PixelFormat::PixelFormatInvalid);
        // initialize pipline
        NS::Error* err = nullptr;
        m_renderPipelineState = mtlDevice->newRenderPipelineState(desc, &err);
        if (err) {
            throw std::runtime_error("failed newRenderPipelineState");
        }
        desc->release();
    }
}
MTL::PrimitiveType MtlRenderingContext::convPrimitiveType(PrimitiveType type)
{
    switch (type) {
    case PrimitiveType::Triangles:
        return MTL::PrimitiveType::PrimitiveTypeTriangle;
    case PrimitiveType::LineStrip:
        return MTL::PrimitiveType::PrimitiveTypeLineStrip;

    default:
        return MTL::PrimitiveType::PrimitiveTypeTriangle;
    }
}
}
#endif