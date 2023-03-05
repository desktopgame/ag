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
    explicit DxSurface(const Window::Instance& window, ComPtr<ID3D12Device> device);
    ~DxSurface();

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
    static ComPtr<ID3D12CommandAllocator> newCommandAllocator(ComPtr<ID3D12Device> device);
    static ComPtr<ID3D12GraphicsCommandList> newCommandList(ComPtr<ID3D12Device> device, ComPtr<ID3D12CommandAllocator> allocator);
    static ComPtr<ID3D12CommandQueue> newCommandQueue(ComPtr<ID3D12Device> device);
    static ComPtr<IDXGISwapChain4> newSwapChain(ComPtr<ID3D12Device> device, ComPtr<ID3D12CommandQueue> queue, const Window::Instance& window);
    static ComPtr<ID3D12DescriptorHeap> newRenderTargetViewHeap(ComPtr<ID3D12Device> device);
    static std::vector<ComPtr<ID3D12Resource>> newRenderTargetView(ComPtr<ID3D12Device> device, ComPtr<IDXGISwapChain4> swapChain, ComPtr<ID3D12DescriptorHeap> descHeap);
    static ComPtr<ID3D12Fence> newFence(ComPtr<ID3D12Device> device, UINT fenceVal);
    static ComPtr<ID3D12Resource> newDepthBuffer(ComPtr<ID3D12Device> device, const Window::Instance& window);
    static ComPtr<ID3D12DescriptorHeap> newDepthStencilViewHeap(ComPtr<ID3D12Device> device);
    static void newDepthStencilView(ComPtr<ID3D12Device> device, ComPtr<ID3D12Resource> depthBuffer, ComPtr<ID3D12DescriptorHeap> descHeap);
    void command(const DxPso::Instance& pso, const std::shared_ptr<DxBuffer> vertex, const std::shared_ptr<DxBuffer> index);
    ComPtr<ID3D12Device> m_device;
    ComPtr<ID3D12CommandAllocator> m_cmdAllocator;
    ComPtr<ID3D12GraphicsCommandList> m_cmdList;
    ComPtr<ID3D12CommandQueue> m_cmdQueue;
    ComPtr<IDXGISwapChain4> m_swapChain;
    ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
    std::vector<ComPtr<ID3D12Resource>> m_backBuffers;
    ComPtr<ID3D12Fence> m_fence;
    ComPtr<ID3D12Resource> m_depthBuffer;
    ComPtr<ID3D12DescriptorHeap> m_depthStencilViewHeap;
    UINT64 m_fenceVal;
    HANDLE m_fenceEvent;
};
}
#endif