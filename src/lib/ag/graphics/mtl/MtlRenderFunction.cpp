#ifdef AG_METAL
#include <ag/Engine.hpp>
#include <ag/Window.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/RenderingContext.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/graphics/mtl/MtlGraphicsDevice.hpp>
#include <ag/graphics/mtl/MtlRenderFunction.hpp>
#include <ag/graphics/mtl/MtlRenderingContext.hpp>
#include <ag/graphics/mtl/MtlShader.hpp>

namespace ag {
MtlRenderFunction::MtlRenderFunction(MtlBufferPool::Instance matrixPool, MtlBufferPool::Instance colorPool)
    : m_matrixPool(matrixPool)
    , m_colorPool(colorPool)
    , m_commandBuffer(nullptr)
    , m_surface(nullptr)
    , m_encoder(nullptr)
{
}
MtlRenderFunction::~MtlRenderFunction()
{
}
void MtlRenderFunction::begin(const std::shared_ptr<Window>& window)
{
    auto mtlDevice = std::static_pointer_cast<MtlGraphicsDevice>(Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice());
    m_commandBuffer = mtlDevice->newCommandBuffer();
    m_surface = window->nextDrawable();
    // create encoder
    auto desc = allocRenderPassDescriptor(window);
    m_encoder = m_commandBuffer->renderCommandEncoder(desc);
    m_encoder->setCullMode(MTL::CullMode::CullModeFront);
    desc->release();
}
void MtlRenderFunction::draw(const std::shared_ptr<RenderingObject>& object)
{
    auto mtlContext = std::static_pointer_cast<MtlRenderingContext>(object->getContext());
    auto mtlShader = std::static_pointer_cast<MtlShader>(object->getShader());
    object->getContext()
        ->setup(object->getShader());
    mtlShader->useTransform(m_encoder, 0, 1);
    if (object->getContext()->getParameter()->useColor1()) {
        mtlShader->useColor1(m_encoder, 0, 2);
    }
    mtlContext->draw(m_encoder, object->getPrimitiveType(), object->getPrimitiveCount());
    mtlShader->release();
    object->getContext()->teardown(object->getShader());
}
void MtlRenderFunction::end(const std::shared_ptr<Window>& window)
{
    m_matrixPool->release();
    m_colorPool->release();
    m_encoder->endEncoding();
    m_encoder = nullptr;
    m_commandBuffer->presentDrawable(m_surface);
    m_commandBuffer->commit();
}
MTL::RenderCommandEncoder* MtlRenderFunction::getRenderCommandEncoder() const
{
    return m_encoder;
}
// private
MTL::RenderPassDescriptor* MtlRenderFunction::allocRenderPassDescriptor(const std::shared_ptr<Window>& window)
{
    auto clearColor = window->getClearColor();
    auto desc = MTL::RenderPassDescriptor::alloc()->init();
    MTL::RenderPassColorAttachmentDescriptor* colorAttachmentDesc = desc->colorAttachments()->object(0);
    colorAttachmentDesc->setClearColor(MTL::ClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0));
    colorAttachmentDesc->setLoadAction(MTL::LoadAction::LoadActionClear);
    colorAttachmentDesc->setStoreAction(MTL::StoreAction::StoreActionStore);
    colorAttachmentDesc->setTexture(m_surface->texture());
    return desc;
}
}
#endif