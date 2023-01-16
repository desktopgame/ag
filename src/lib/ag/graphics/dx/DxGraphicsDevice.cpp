#ifdef AG_DIRECT_X
#include <ag/Engine.hpp>
#include <ag/graphics/dx/DxBuffer.hpp>
#include <ag/graphics/dx/DxGraphicsDevice.hpp>
#include <ag/graphics/dx/DxGraphicsDriver.hpp>
#include <ag/graphics/dx/DxRenderingContext.hpp>
#include <ag/graphics/dx/DxTexture.hpp>
#include <ag/native/glfw.hpp>
#include <stdexcept>

namespace ag {
DxGraphicsDevice::DxGraphicsDevice(ID3D12Device* device)
    : m_device(device)
{
}
std::shared_ptr<ITexture> DxGraphicsDevice::newTexture(int width, int height, const uint8_t* data) const { return std::make_shared<DxTexture>(); }
std::shared_ptr<IBuffer> DxGraphicsDevice::newVertexBuffer() const { return std::make_shared<DxBuffer>(m_device); }
std::shared_ptr<IBuffer> DxGraphicsDevice::newIndexBuffer() const { return std::make_shared<DxBuffer>(m_device); }
std::shared_ptr<RenderingContext> DxGraphicsDevice::newRenderingContext() const { return std::make_shared<DxRenderingContext>(); }
std::shared_ptr<DxSurface> DxGraphicsDevice::newSurface(const Window::Instance& window) const { return std::make_shared<DxSurface>(window, m_device); }
}
#endif