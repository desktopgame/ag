#include <ag/Engine.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/mtl/MtlBuffer.hpp>
#include <ag/graphics/mtl/MtlGraphicsDevice.hpp>
#include <ag/graphics/mtl/MtlRenderingContext.hpp>
#include <ag/graphics/mtl/MtlShader.hpp>

#ifdef AG_METAL

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
        mtlShader->attach(desc);
        desc->colorAttachments()->object(0)->setPixelFormat(
            MTL::PixelFormatBGRA8Unorm);
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
void MtlRenderingContext::draw(MTL::RenderCommandEncoder* encoder)
{
    auto mtlVertex = std::static_pointer_cast<MtlBuffer>(m_vertex);
    auto mtlIndex = std::static_pointer_cast<MtlBuffer>(m_index);
    encoder->setRenderPipelineState(m_renderPipelineState);
    mtlVertex->attachAsVertex(encoder, 0, 0);
    if (m_indexLength > 0) {
        mtlIndex->drawWithIndex(encoder, MTL::PrimitiveType::PrimitiveTypeTriangle);
    } else {
    }
    /*
    encoder->setRenderPipelineState(m_renderPipelineState);
    encoder->setVertexBuffer(m_vertexBuffer, 0, kShaderVertexInputIndexVertices);
    encoder->setVertexBuffer(m_cameraBuffer, 0, kShaderVertexInputIndexCamera);
    encoder->drawIndexedPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, 6,
        MTL::IndexType::IndexTypeUInt16, m_indexBuffer,
        0);
    */
}
void MtlRenderingContext::teardown(const std::shared_ptr<IShader>& shader) { }
}
#endif