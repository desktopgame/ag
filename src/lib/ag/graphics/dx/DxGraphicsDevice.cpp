#include <ag/Engine.hpp>
#include <ag/graphics/dx/DxGraphicsDevice.hpp>
#include <ag/graphics/dx/DxGraphicsDriver.hpp>
#include <ag/native/glfw.hpp>
#include <stdexcept>

namespace ag {
DxGraphicsDevice::DxGraphicsDevice(ID3D12Device* device)
    : m_device(device)
{
}
std::shared_ptr<ITexture> DxGraphicsDevice::newTexture(int width, int height, const uint8_t* data) const { return nullptr; }
std::shared_ptr<IBuffer> DxGraphicsDevice::newVertexBuffer() const { return nullptr; }
std::shared_ptr<IBuffer> DxGraphicsDevice::newIndexBuffer() const { return nullptr; }
std::shared_ptr<RenderingContext> DxGraphicsDevice::newRenderingContext() const { return nullptr; }
ID3D12CommandAllocator* DxGraphicsDevice::newCommandAllocator() const
{
    ID3D12CommandAllocator* ret;
    if (m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
            IID_PPV_ARGS(&ret))) {
        throw std::runtime_error("failed CreateCommandAllocator()");
    }
    return ret;
}
ID3D12GraphicsCommandList* DxGraphicsDevice::newCommandList(ID3D12CommandAllocator* allocator) const
{
    ID3D12GraphicsCommandList* ret;
    if (m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator,
            nullptr, IID_PPV_ARGS(&ret))) {
        throw std::runtime_error("failed CreateCommandList()");
    }
    return ret;
}

ID3D12CommandQueue* DxGraphicsDevice::newCommandQueue() const
{
    ID3D12CommandQueue* ret;
    D3D12_COMMAND_QUEUE_DESC desc = {};
    desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    desc.NodeMask = 0;
    desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    if (FAILED(m_device->CreateCommandQueue(&desc, IID_PPV_ARGS(&ret)))) {
        throw std::runtime_error("failed CreateCommandQueue()");
    }
    return ret;
}

IDXGISwapChain4* DxGraphicsDevice::newSwapChain(ID3D12CommandQueue* queue, const Window::Instance& window) const
{
    IDXGISwapChain4* ret;
    DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
    swapchainDesc.Width = 1280;
    swapchainDesc.Height = 720;
    swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapchainDesc.Stereo = false;
    swapchainDesc.SampleDesc.Count = 1;
    swapchainDesc.SampleDesc.Quality = 0;
    swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
    swapchainDesc.BufferCount = 2;
    swapchainDesc.Scaling = DXGI_SCALING_STRETCH;
    swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    IDXGIFactory6* dxgiFactory = std::static_pointer_cast<DxGraphicsDriver>(Engine::getInstance()->getGraphicsDriver())->getDXGIFactory();
    if (FAILED(dxgiFactory->CreateSwapChainForHwnd(
            queue, getWin32Window(window->getNativeWindow()), &swapchainDesc, nullptr, nullptr,
            (IDXGISwapChain1**)&ret))) {
        throw std::runtime_error("failed CreateSwapChainForHwnd()");
    }
    return ret;
}

ID3D12DescriptorHeap* DxGraphicsDevice::newRenderTargetViewHeap() const
{
    ID3D12DescriptorHeap* ret;
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
    desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    desc.NodeMask = 0;
    desc.NumDescriptors = 2;
    desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    if (FAILED(m_device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&ret)))) {
        throw std::runtime_error("failed CreateDescriptorHeap()");
    }
    return ret;
}

std::vector<ID3D12Resource*> DxGraphicsDevice::newRenderTargetView(IDXGISwapChain4* swapChain, ID3D12DescriptorHeap* descHeap) const
{
    std::vector<ID3D12Resource*> ret;
    DXGI_SWAP_CHAIN_DESC swcDesc = {};
    if (FAILED(swapChain->GetDesc(&swcDesc))) {
        throw std::runtime_error("failed GetDesc()");
    }
    D3D12_CPU_DESCRIPTOR_HANDLE handle = descHeap->GetCPUDescriptorHandleForHeapStart();
    for (size_t i = 0; i < swcDesc.BufferCount; ++i) {
        ret.push_back(nullptr);
        if (FAILED(swapChain->GetBuffer(static_cast<UINT>(i),
                IID_PPV_ARGS(&ret.at(i))))) {
            throw std::runtime_error("failed GetBuffer()");
        }
        m_device->CreateRenderTargetView(ret.at(i), nullptr, handle);
        handle.ptr += m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    }
}

ID3D12Fence* DxGraphicsDevice::newFence(UINT fenceVal) const
{
    ID3D12Fence* ret;
    if (FAILED(m_device->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE,
            IID_PPV_ARGS(&ret)))) {
        throw std::runtime_error("failed CreateFence()");
    }
    return ret;
}
}