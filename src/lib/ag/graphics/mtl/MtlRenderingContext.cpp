#include <ag/Engine.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
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
}
void MtlRenderingContext::teardown(const std::shared_ptr<IShader>& shader) { }
}
#endif