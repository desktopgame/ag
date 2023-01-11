#pragma once
#ifdef AG_DIRECT_X
#include <ag/Window.hpp>
#include <ag/graphics/IGraphicsDevice.hpp>
#include <ag/native/dx.hpp>

namespace ag {
class DxGraphicsDevice : public IGraphicsDevice {
public:
    explicit DxGraphicsDevice(ID3D12Device* device);

    std::shared_ptr<ITexture> newTexture(int width, int height, const uint8_t* data) const override;
    std::shared_ptr<IBuffer> newVertexBuffer() const override;
    std::shared_ptr<IBuffer> newIndexBuffer() const override;
    std::shared_ptr<RenderingContext> newRenderingContext() const override;
    ID3D12CommandAllocator* newCommandAllocator() const;
    ID3D12GraphicsCommandList* newCommandList(ID3D12CommandAllocator* allocator) const;
    ID3D12CommandQueue* newCommandQueue() const;
    IDXGISwapChain4* newSwapChain(ID3D12CommandQueue* queue, const Window::Instance& window) const;
    ID3D12DescriptorHeap* newRenderTargetViewHeap() const;
    std::vector<ID3D12Resource*> newRenderTargetView(IDXGISwapChain4* swapChain, ID3D12DescriptorHeap* descHeap) const;
    ID3D12Fence* newFence(UINT fenceVal) const;

private:
    ID3D12Device* m_device;
};
}
#endif