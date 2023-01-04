#ifdef AG_METAL
#include <ag/Engine.hpp>
#include <ag/Window.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/RenderPass.hpp>
#include <ag/graphics/RenderingContext.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/graphics/mtl/MtlGraphicsDevice.hpp>
#include <ag/graphics/mtl/MtlRenderFunction.hpp>
#include <ag/graphics/mtl/MtlRenderingContext.hpp>
#include <ag/graphics/mtl/MtlShader.hpp>

namespace ag {
MtlRenderFunction::MtlRenderFunction(MtlUniformManager::Instance uniformManager)
    : m_uniformManager(uniformManager)
    , m_commandBuffer(nullptr)
    , m_surface(nullptr)
    , m_encoder(nullptr)
{
}
MtlRenderFunction::~MtlRenderFunction()
{
}
void MtlRenderFunction::begin(const std::shared_ptr<Window>& window, const RenderPass& pass)
{
    auto mtlDevice = std::static_pointer_cast<MtlGraphicsDevice>(Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice());
    m_arPool = NS::AutoreleasePool::alloc()->init();
    m_uniformManager->next();
    // sync buffer
    MtlRenderFunction* self = this;
    m_uniformManager->waitSync();
    m_commandBuffer->addCompletedHandler([self](auto _) -> void {
        self->m_uniformManager->signal();
    });
    // create encoder
    auto desc = newRenderPassDescriptor(window);
    m_encoder = m_commandBuffer->renderCommandEncoder(desc);
    if (pass.renderMode == ag::RenderMode::Render3D) {
        auto ddesc = MTL::DepthStencilDescriptor::alloc()->init();
        ddesc->setDepthCompareFunction(MTL::CompareFunctionLess);
        ddesc->setDepthWriteEnabled(true);
        auto depthStencilState = mtlDevice->newDepthStencilState(ddesc);
        m_encoder->setDepthStencilState(depthStencilState);
        ddesc->release();
    }
    m_encoder->setCullMode(MTL::CullMode::CullModeBack);
    m_encoder->setFrontFacingWinding(MTL::Winding::WindingClockwise);
    desc->release();
}
void MtlRenderFunction::end()
{
    m_uniformManager->releaseAll();
    m_encoder->endEncoding();
    //m_encoder->release();
    //m_commandBuffer->release();
    m_arPool->release();
}

void MtlRenderFunction::clear(const std::shared_ptr<Window>& window)
{
    auto mtlDevice = std::static_pointer_cast<MtlGraphicsDevice>(Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice());
    m_shouldClear = true;
    m_commandBuffer = mtlDevice->newCommandBuffer();
    m_surface = window->nextDrawable();
}

void MtlRenderFunction::present(const std::shared_ptr<Window>& window)
{
    m_commandBuffer->presentDrawable(m_surface);
    m_commandBuffer->commit();
    m_commandBuffer->release();
}
MTL::RenderCommandEncoder* MtlRenderFunction::getRenderCommandEncoder() const
{
    return m_encoder;
}
// private
MTL::RenderPassDescriptor* MtlRenderFunction::newRenderPassDescriptor(const std::shared_ptr<Window>& window)
{
    auto clearColor = window->getClearColor();
    auto desc = MTL::RenderPassDescriptor::alloc()->init();
    MTL::RenderPassColorAttachmentDescriptor* colorAttachmentDesc = desc->colorAttachments()->object(0);
    if (m_shouldClear) {
        m_shouldClear = false;
        colorAttachmentDesc->setClearColor(MTL::ClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0));
        colorAttachmentDesc->setLoadAction(MTL::LoadAction::LoadActionClear);
        colorAttachmentDesc->setStoreAction(MTL::StoreAction::StoreActionStore);
        colorAttachmentDesc->setTexture(m_surface->texture());
        desc->depthAttachment()->setClearDepth(1.0f);
        desc->depthAttachment()->setLoadAction(MTL::LoadActionClear);
        desc->depthAttachment()->setStoreAction(MTL::StoreAction::StoreActionStore);
    } else {
        colorAttachmentDesc->setClearColor(MTL::ClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0));
        colorAttachmentDesc->setLoadAction(MTL::LoadAction::LoadActionLoad);
        colorAttachmentDesc->setStoreAction(MTL::StoreAction::StoreActionStore);
        colorAttachmentDesc->setTexture(m_surface->texture());
        desc->depthAttachment()->setClearDepth(1.0f);
        desc->depthAttachment()->setLoadAction(MTL::LoadActionLoad);
        desc->depthAttachment()->setStoreAction(MTL::StoreAction::StoreActionStore);
    }
    return desc;
}
}
#endif