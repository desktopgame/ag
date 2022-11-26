#include <ag/graphics/mtl/MtlGraphicsDevice.hpp>

namespace ag {
MtlGraphicsDevice::MtlGraphicsDevice()
    : m_device(MTL::CreateSystemDefaultDevice())
    , m_commandQueue()
{
    m_commandQueue = m_device->newCommandQueue();
}
MtlGraphicsDevice::~MtlGraphicsDevice()
{
    m_device->release();
    m_commandQueue->release();
}
std::shared_ptr<ITexture> MtlGraphicsDevice::newTexture(int width, int height, const uint8_t* data) const
{
    m_device->retain();
    m_commandQueue->retain();
    return nullptr;
}
std::shared_ptr<IBuffer> MtlGraphicsDevice::newVertexBuffer() const
{
    return nullptr;
}
std::shared_ptr<IBuffer> MtlGraphicsDevice::newIndexBuffer() const
{
    return nullptr;
}
}