#ifdef AG_DIRECT_X
#include <ag/Engine.hpp>
#include <ag/graphics/IGraphicsDevice.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/dx/DxGraphicsDevice.hpp>
#include <ag/graphics/dx/DxGraphicsDriver.hpp>
#include <ag/graphics/dx/DxSurface.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
DxSurface::DxSurface(const Window::Instance& window, ID3D12Device* device)
    : m_device(device)
    , m_cmdAllocator(nullptr)
    , m_cmdList(nullptr)
    , m_cmdQueue(nullptr)
    , m_swapChain(nullptr)
    , m_rtvHeap(nullptr)
    , m_backBuffers()
    , m_fence(nullptr)
    , m_fenceVal(0)
{
    m_cmdAllocator = newCommandAllocator(device);
    m_cmdList = newCommandList(device, m_cmdAllocator);
    m_cmdQueue = newCommandQueue(device);
    m_swapChain = newSwapChain(device, m_cmdQueue, window);
    m_rtvHeap = newRenderTargetViewHeap(device);
    m_backBuffers = newRenderTargetView(device, m_swapChain, m_rtvHeap);
    m_fence = newFence(device, 0);
}

void DxSurface::transitionPresentToRender()
{
    int bbIdx = m_swapChain->GetCurrentBackBufferIndex();
    D3D12_RESOURCE_BARRIER barrierDesc = {};
    barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrierDesc.Transition.pResource = m_backBuffers[bbIdx];
    barrierDesc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    m_cmdList->ResourceBarrier(1, &barrierDesc);
}
void DxSurface::transitionRenderToPresent()
{
    int bbIdx = m_swapChain->GetCurrentBackBufferIndex();
    D3D12_RESOURCE_BARRIER barrierDesc = {};
    barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrierDesc.Transition.pResource = m_backBuffers[bbIdx];
    barrierDesc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    m_cmdList->ResourceBarrier(1, &barrierDesc);
}
void DxSurface::clear(const glm::vec3& color)
{
    int bbIdx = m_swapChain->GetCurrentBackBufferIndex();
    // レンダーターゲットを指定
    auto rtvH = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
    rtvH.ptr += static_cast<ULONG_PTR>(bbIdx * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
    m_cmdList->OMSetRenderTargets(1, &rtvH, false, nullptr);

    // 画面クリア
    m_cmdList->ClearRenderTargetView(rtvH, &color.r, 0, nullptr);
}
void DxSurface::execute()
{
    // 命令のクローズ
    m_cmdList->Close();

    // コマンドリストの実行
    ID3D12CommandList* cmdlists[] = { m_cmdList };
    m_cmdQueue->ExecuteCommandLists(1, cmdlists);
}
void DxSurface::reset()
{
    m_cmdAllocator->Reset(); // キューをクリア
    m_cmdList->Reset(m_cmdAllocator, nullptr); // 再びコマンドリストをためる準備
}
void DxSurface::waitSync()
{
    m_cmdQueue->Signal(m_fence, ++m_fenceVal);
    if (m_fence->GetCompletedValue() != m_fenceVal) {
        auto event = CreateEvent(nullptr, false, false, nullptr);
        m_fence->SetEventOnCompletion(m_fenceVal, event);
        WaitForSingleObject(event, INFINITE);
        CloseHandle(event);
    }
}
void DxSurface::present()
{
    m_swapChain->Present(1, 0);
}
// private
ID3D12CommandAllocator* DxSurface::newCommandAllocator(ID3D12Device* device)
{
    ID3D12CommandAllocator* ret;
    if (device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
            IID_PPV_ARGS(&ret))) {
        throw std::runtime_error("failed CreateCommandAllocator()");
    }
    return ret;
}
ID3D12GraphicsCommandList* DxSurface::newCommandList(ID3D12Device* device, ID3D12CommandAllocator* allocator)
{
    ID3D12GraphicsCommandList* ret;
    if (device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator,
            nullptr, IID_PPV_ARGS(&ret))) {
        throw std::runtime_error("failed CreateCommandList()");
    }
    return ret;
}
ID3D12CommandQueue* DxSurface::newCommandQueue(ID3D12Device* device)
{
    ID3D12CommandQueue* ret;
    D3D12_COMMAND_QUEUE_DESC desc = {};
    desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    desc.NodeMask = 0;
    desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    if (FAILED(device->CreateCommandQueue(&desc, IID_PPV_ARGS(&ret)))) {
        throw std::runtime_error("failed CreateCommandQueue()");
    }
    return ret;
}
IDXGISwapChain4* DxSurface::newSwapChain(ID3D12Device* device, ID3D12CommandQueue* queue, const Window::Instance& window)
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
ID3D12DescriptorHeap* DxSurface::newRenderTargetViewHeap(ID3D12Device* device)
{
    ID3D12DescriptorHeap* ret;
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
    desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    desc.NodeMask = 0;
    desc.NumDescriptors = 2;
    desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    if (FAILED(device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&ret)))) {
        throw std::runtime_error("failed CreateDescriptorHeap()");
    }
    return ret;
}
std::vector<ID3D12Resource*> DxSurface::newRenderTargetView(ID3D12Device* device, IDXGISwapChain4* swapChain, ID3D12DescriptorHeap* descHeap)
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
        device->CreateRenderTargetView(ret.at(i), nullptr, handle);
        handle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    }
    return ret;
}
ID3D12Fence* DxSurface::newFence(ID3D12Device* device, UINT fenceVal)
{
    ID3D12Fence* ret;
    if (FAILED(device->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE,
            IID_PPV_ARGS(&ret)))) {
        throw std::runtime_error("failed CreateFence()");
    }
    return ret;
}
}

#endif