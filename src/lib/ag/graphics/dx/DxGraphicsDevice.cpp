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
DxGraphicsDevice::DxGraphicsDevice(ComPtr<ID3D12Device> device)
    : m_device(device)
{
}
std::shared_ptr<ITexture> DxGraphicsDevice::newTexture(int width, int height, const uint8_t* data) const
{
    auto dxTex = std::make_shared<DxTexture>(m_device);
    dxTex->update(width, height, data);
    return dxTex;
}
std::shared_ptr<IBuffer> DxGraphicsDevice::newVertexBuffer() const { return std::make_shared<DxBuffer>(m_device); }
std::shared_ptr<IBuffer> DxGraphicsDevice::newIndexBuffer() const { return std::make_shared<DxBuffer>(m_device); }
std::shared_ptr<RenderingContext> DxGraphicsDevice::newRenderingContext() const { return std::make_shared<DxRenderingContext>(); }
std::shared_ptr<DxSurface> DxGraphicsDevice::newSurface(const Window::Instance& window) const { return std::make_shared<DxSurface>(window, m_device.Get()); }
std::shared_ptr<DxPso> DxGraphicsDevice::newPso(const std::shared_ptr<DxShader>& shader,
    const std::shared_ptr<ShaderParameter>& shaderParameter,
    PrimitiveType primitiveType,
    int vertexComponent,
    bool isUsingTexCoord)
{
    auto pso = std::make_shared<DxPso>(shader, shaderParameter, primitiveType, vertexComponent, isUsingTexCoord);
    pso->init(m_device);
    return pso;
}
}
#endif