#pragma once
#ifdef AG_DIRECT_X
#include <ag/Window.hpp>
#include <ag/graphics/dx/DxBuffer.hpp>
#include <ag/graphics/dx/DxPso.hpp>
#include <ag/native/dx.hpp>
#include <memory>
#include <vector>

namespace ag {
class DxSurface {
public:
    using Instance = std::shared_ptr<DxSurface>;
    explicit DxSurface(const Window::Instance& window, ID3D12Device* device);

    void transitionPresentToRender();
    void transitionRenderToPresent();
    void clear(const glm::vec3& color);
    void resolution(const glm::ivec2& size);
    void draw(const DxPso::Instance& pso, const std::shared_ptr<DxBuffer> vertex, int vertexCount);
    void draw(const DxPso::Instance& pso, const std::shared_ptr<DxBuffer> vertex, const std::shared_ptr<DxBuffer> index, int indexCount);
    void execute();
    void reset();
    void waitSync();
    void present();

private:
    static ID3D12CommandAllocator* newCommandAllocator(ID3D12Device* device);
    static ID3D12GraphicsCommandList* newCommandList(ID3D12Device* device, ID3D12CommandAllocator* allocator);
    static ID3D12CommandQueue* newCommandQueue(ID3D12Device* device);
    static IDXGISwapChain4* newSwapChain(ID3D12Device* device, ID3D12CommandQueue* queue, const Window::Instance& window);
    static ID3D12DescriptorHeap* newRenderTargetViewHeap(ID3D12Device* device);
    static std::vector<ID3D12Resource*> newRenderTargetView(ID3D12Device* device, IDXGISwapChain4* swapChain, ID3D12DescriptorHeap* descHeap);
    static ID3D12Fence* newFence(ID3D12Device* device, UINT fenceVal);
    static ID3D12Resource* newDepthBuffer(ID3D12Device* device, const Window::Instance& window);
    static ID3D12DescriptorHeap* newDepthStencilViewHeap(ID3D12Device* device);
    static void newDepthStencilView(ID3D12Device* device, ID3D12Resource* depthBuffer, ID3D12DescriptorHeap* descHeap);
    void command(const DxPso::Instance& pso, const std::shared_ptr<DxBuffer> vertex, const std::shared_ptr<DxBuffer> index);
    ID3D12Device* m_device;
    ID3D12CommandAllocator* m_cmdAllocator;
    ID3D12GraphicsCommandList* m_cmdList;
    ID3D12CommandQueue* m_cmdQueue;
    IDXGISwapChain4* m_swapChain;
    ID3D12DescriptorHeap* m_rtvHeap;
    std::vector<ID3D12Resource*> m_backBuffers;
    ID3D12Fence* m_fence;
    ID3D12Resource* m_depthBuffer;
    ID3D12DescriptorHeap* m_depthStencilViewHeap;
    UINT m_fenceVal;
};
}
#endif