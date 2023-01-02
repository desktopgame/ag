#ifdef AG_METAL
#include <ag/graphics/mtl/MtlBuffer.hpp>
#include <ag/graphics/mtl/MtlGraphicsDevice.hpp>
#include <ag/graphics/mtl/MtlRenderingContext.hpp>
#include <ag/graphics/mtl/MtlTexture.hpp>

namespace ag {
MtlGraphicsDevice::MtlGraphicsDevice(MTL::Device* device)
    : m_device(device)
    , m_commandQueue()
{
    m_device->retain();
    m_commandQueue = m_device->newCommandQueue();
}
MtlGraphicsDevice::~MtlGraphicsDevice()
{
    m_device->release();
    m_commandQueue->release();
}
std::shared_ptr<ITexture> MtlGraphicsDevice::newTexture(int width, int height, const uint8_t* data) const
{
    auto tex = std::make_shared<MtlTexture>(m_device);
    tex->update(width, height, data);
    return tex;
}
std::shared_ptr<IBuffer> MtlGraphicsDevice::newVertexBuffer() const
{
    return std::make_shared<MtlBuffer>(m_device);
}
std::shared_ptr<IBuffer> MtlGraphicsDevice::newIndexBuffer() const
{
    return std::make_shared<MtlBuffer>(m_device);
}
std::shared_ptr<RenderingContext> MtlGraphicsDevice::newRenderingContext() const
{
    return std::make_shared<MtlRenderingContext>();
}
MTL::RenderPipelineState* MtlGraphicsDevice::newRenderPipelineState(const MTL::RenderPipelineDescriptor* desc, NS::Error** err) const
{
    return m_device->newRenderPipelineState(desc, err);
}
MTL::CommandBuffer* MtlGraphicsDevice::newCommandBuffer() const
{
    return m_commandQueue->commandBuffer();
}
}
#endif