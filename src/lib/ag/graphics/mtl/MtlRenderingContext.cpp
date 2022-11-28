#ifdef AG_METAL
#include <ag/Engine.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/ShaderParameter.hpp>
#include <ag/graphics/mtl/MtlBuffer.hpp>
#include <ag/graphics/mtl/MtlGraphicsDevice.hpp>
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
void MtlRenderingContext::setup(const std::shared_ptr<IShader>& shader)
{
    auto mtlShader = std::static_pointer_cast<MtlShader>(shader);
    auto mtlDevice = std::static_pointer_cast<MtlGraphicsDevice>(Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice());
    if (!m_renderPipelineState) {
        MTL::RenderPipelineDescriptor* desc = MTL::RenderPipelineDescriptor::alloc()->init();
        MTL::RenderPipelineColorAttachmentDescriptor* colorDesc = desc->colorAttachments()->object(0);
        mtlShader->attach(desc);
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
    shader->apply(m_parameter);
}
void MtlRenderingContext::draw(MTL::RenderCommandEncoder* encoder, PrimitiveType type, int primCount)
{
    auto mtlVertex = std::static_pointer_cast<MtlBuffer>(m_vertex);
    auto mtlIndex = std::static_pointer_cast<MtlBuffer>(m_index);
    encoder->setRenderPipelineState(m_renderPipelineState);
    mtlVertex->attachAsVertex(encoder, 0, 0);
    if (m_parameter->useTexture()) {
        auto mtlTexture = std::static_pointer_cast<MtlTexture>(m_parameter->getTexture());
        mtlTexture->attach(encoder, 2);
    }
    if (m_indexLength > 0) {
        mtlIndex->drawWithIndex(encoder, convPrimitiveType(type));
    } else {
        NS::UInteger nsOffs = static_cast<NS::UInteger>(0);
        NS::UInteger nsPrimCount = static_cast<NS::UInteger>(primCount);
        encoder->drawPrimitives(convPrimitiveType(type), nsOffs, nsPrimCount);
    }
}
void MtlRenderingContext::teardown(const std::shared_ptr<IShader>& shader) { }
// private
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