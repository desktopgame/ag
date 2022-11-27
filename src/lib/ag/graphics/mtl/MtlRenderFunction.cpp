#include <ag/Engine.hpp>
#include <ag/Window.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/RenderingContext.hpp>
#include <ag/graphics/RenderingObject.hpp>
#include <ag/graphics/mtl/MtlGraphicsDevice.hpp>
#include <ag/graphics/mtl/MtlRenderFunction.hpp>
#include <ag/graphics/mtl/MtlRenderingContext.hpp>
#ifdef AG_METAL

namespace ag {
MtlRenderFunction::MtlRenderFunction()
    : m_commandBuffer(nullptr)
    , m_surface(nullptr)
    , m_passDesc(nullptr)
{
}
MtlRenderFunction::~MtlRenderFunction()
{
    if (m_commandBuffer) {
        m_commandBuffer->release();
        m_commandBuffer = nullptr;
    }
}
void MtlRenderFunction::begin(const std::shared_ptr<Window>& window)
{
    auto mtlDevice = std::static_pointer_cast<MtlGraphicsDevice>(Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice());
    m_commandBuffer = mtlDevice->newCommandBuffer();
    m_surface = window->nextDrawable();
    m_passDesc = MTL::RenderPassDescriptor::alloc()->init();
    MTL::RenderPassColorAttachmentDescriptor* colorAttachmentDesc = m_passDesc->colorAttachments()->object(0);
    colorAttachmentDesc->setClearColor(MTL::ClearColor(1.0, 0.0, 0.0, 1.0));
    colorAttachmentDesc->setLoadAction(MTL::LoadAction::LoadActionClear);
    colorAttachmentDesc->setStoreAction(MTL::StoreAction::StoreActionStore);
    colorAttachmentDesc->setTexture(m_surface->texture());
}
void MtlRenderFunction::draw(const std::shared_ptr<RenderingObject>& object)
{
    auto mtlContext = std::static_pointer_cast<MtlRenderingContext>(object->getContext());
    object->getContext()->setup(object->getShader());
    MTL::RenderCommandEncoder* encoder = m_commandBuffer->renderCommandEncoder(m_passDesc);
    mtlContext->draw(encoder);
    encoder->endEncoding();
    object->getContext()->teardown(object->getShader());
}
void MtlRenderFunction::end(const std::shared_ptr<Window>& window)
{
    if (m_commandBuffer) {
        m_commandBuffer->release();
        m_commandBuffer = nullptr;
    }
    if (m_passDesc) {
        m_passDesc->release();
        m_passDesc = nullptr;
    }
    m_commandBuffer->presentDrawable(m_surface);
    m_commandBuffer->commit();
}
}
#endif