#ifdef AG_METAL
#include <ag/Engine.hpp>
#include <ag/Window.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/IRenderFunction.hpp>
#include <ag/graphics/RenderPass.hpp>
#include <ag/graphics/RenderingContext.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/graphics/mtl/MtlGraphicsDevice.hpp>
#include <ag/graphics/mtl/MtlGraphicsDriver.hpp>
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
void MtlRenderFunction::link(const std::shared_ptr<Window>& window)
{
    if (window->getSurfaceObject().has_value()) {
        return;
    }
    CA::MetalLayer* layer = CA::MetalLayer::alloc()->init();
    layer->setOpaque(true);
    std::static_pointer_cast<MtlGraphicsDriver>(Engine::getInstance()->getGraphicsDriver())->useDevice(layer);
    NS::Window* nsWindow = NS::Window::bridgingCast(getCocoaWindow(window->getNativeWindow()));
    NS::View* contentView = nsWindow->contentView();
    contentView->setLayer(layer);
    contentView->setWantsLayer(true);
    window->setSurfaceObject(layer);
}
void MtlRenderFunction::begin(const std::shared_ptr<Window>& window, const RenderPass& pass)
{
    auto mtlDevice = std::static_pointer_cast<MtlGraphicsDevice>(Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice());
    m_uniformManager->next();
    // sync buffer
    MtlRenderFunction* self = this;
    m_uniformManager->waitSync();
    m_commandBuffer->addCompletedHandler([self](auto _) -> void {
        self->m_uniformManager->signal();
    });
    // create encoder
    auto renderPassDesc = newRenderPassDescriptor(window);
    auto depthStencilDesc = newDepthStencilDescriptor(pass);
    auto depthStencilState = mtlDevice->newDepthStencilState(depthStencilDesc);
    m_encoder = m_commandBuffer->renderCommandEncoder(renderPassDesc);
    m_encoder->setDepthStencilState(depthStencilState);
    m_encoder->setCullMode(MTL::CullMode::CullModeBack);
    m_encoder->setFrontFacingWinding(MTL::Winding::WindingClockwise);
    renderPassDesc->release();
    depthStencilDesc->release();
    depthStencilState->release();
}
void MtlRenderFunction::end()
{
    m_uniformManager->releaseAll();
    m_encoder->endEncoding();
    //m_encoder->release();
}

void MtlRenderFunction::clear(const std::shared_ptr<Window>& window)
{
    auto mtlDevice = std::static_pointer_cast<MtlGraphicsDevice>(Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice());
    m_arPool = NS::AutoreleasePool::alloc()->init();
    m_shouldClear = true;
    m_commandBuffer = mtlDevice->newCommandBuffer();
    m_surface = std::any_cast<CA::MetalLayer*>(window->getSurfaceObject())->nextDrawable();
}

void MtlRenderFunction::present(const std::shared_ptr<Window>& window)
{
    m_commandBuffer->presentDrawable(m_surface);
    m_commandBuffer->commit();
    m_arPool->release();
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

MTL::DepthStencilDescriptor* MtlRenderFunction::newDepthStencilDescriptor(const RenderPass& renderPass)
{
    auto mtlDevice = std::static_pointer_cast<MtlGraphicsDevice>(Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice());
    auto desc = MTL::DepthStencilDescriptor::alloc()->init();
    if (renderPass.renderMode == RenderMode::Render2D) {
        desc->setDepthCompareFunction(MTL::CompareFunctionAlways);
        desc->setDepthWriteEnabled(false);
    } else if (renderPass.renderMode == RenderMode::Render3D) {
        desc->setDepthCompareFunction(MTL::CompareFunctionLess);
        desc->setDepthWriteEnabled(true);
    }
    return desc;
}
}
#endif