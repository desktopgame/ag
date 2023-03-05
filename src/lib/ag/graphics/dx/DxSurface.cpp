#ifdef AG_DIRECT_X
#include <ag/Engine.hpp>
#include <ag/graphics/IGraphicsDevice.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/VertexData2D.hpp>
#include <ag/graphics/VertexData3D.hpp>
#include <ag/graphics/dx/DxGraphicsDevice.hpp>
#include <ag/graphics/dx/DxGraphicsDriver.hpp>
#include <ag/graphics/dx/DxSurface.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
DxSurface::DxSurface(const Window::Instance& window, ComPtr<ID3D12Device> device)
    : m_device(device)
    , m_cmdAllocator(nullptr)
    , m_cmdList(nullptr)
    , m_cmdQueue(nullptr)
    , m_swapChain(nullptr)
    , m_rtvHeap(nullptr)
    , m_backBuffers()
    , m_fence(nullptr)
    , m_depthBuffer(nullptr)
    , m_depthStencilViewHeap(nullptr)
    , m_fenceVal(0)
    , m_fenceEvent(nullptr)
{
    m_cmdAllocator = newCommandAllocator(device);
    m_cmdList = newCommandList(device, m_cmdAllocator);
    m_cmdQueue = newCommandQueue(device);
    m_swapChain = newSwapChain(device, m_cmdQueue, window);
    m_rtvHeap = newRenderTargetViewHeap(device);
    m_backBuffers = newRenderTargetView(device, m_swapChain, m_rtvHeap);
    m_fence = newFence(device, 0);
    m_depthBuffer = newDepthBuffer(device, window);
    m_depthStencilViewHeap = newDepthStencilViewHeap(device);
    newDepthStencilView(device, m_depthBuffer, m_depthStencilViewHeap);
}
DxSurface::~DxSurface()
{
    if (m_fenceEvent) {
        CloseHandle(m_fenceEvent);
        m_fenceEvent = nullptr;
    }
}

void DxSurface::transitionPresentToRender()
{
    int bbIdx = m_swapChain->GetCurrentBackBufferIndex();
    D3D12_RESOURCE_BARRIER barrierDesc = {};
    barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrierDesc.Transition.pResource = m_backBuffers[bbIdx].Get();
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
    barrierDesc.Transition.pResource = m_backBuffers[bbIdx].Get();
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
    auto dsvH = m_depthStencilViewHeap->GetCPUDescriptorHandleForHeapStart();
    m_cmdList->OMSetRenderTargets(1, &rtvH, false, &dsvH);

    // 画面クリア
    m_cmdList->ClearRenderTargetView(rtvH, &color.r, 0, nullptr);
    m_cmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}
void DxSurface::resolution(const glm::ivec2& size)
{
    // viewport
    D3D12_VIEWPORT viewport = {};
    viewport.Width = size.x;
    viewport.Height = size.y;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.MaxDepth = 1.0f;
    viewport.MinDepth = 0.0f;
    m_cmdList->RSSetViewports(1, &viewport);
    // scissor
    D3D12_RECT scissorRect = {};
    scissorRect.top = 0;
    scissorRect.left = 0;
    scissorRect.right = scissorRect.left + size.x;
    scissorRect.bottom = scissorRect.top + size.y;
    m_cmdList->RSSetScissorRects(1, &scissorRect);
}

void DxSurface::draw(const DxPso::Instance& pso, const std::shared_ptr<DxBuffer> vertex, int vertexCount)
{
    command(pso, vertex, nullptr);
    m_cmdList->DrawInstanced(vertexCount, 1, 0, 0);
}
void DxSurface::draw(const DxPso::Instance& pso, const std::shared_ptr<DxBuffer> vertex, const std::shared_ptr<DxBuffer> index, int indexCount)
{
    command(pso, vertex, index);
    m_cmdList->DrawIndexedInstanced(indexCount, 1, 0, 0, 0);
}
void DxSurface::execute()
{
    // 命令のクローズ
    m_cmdList->Close();

    // コマンドリストの実行
    ID3D12CommandList* cmdlists[] = { m_cmdList.Get() };
    m_cmdQueue->ExecuteCommandLists(1, cmdlists);
}
void DxSurface::reset()
{
    m_cmdAllocator->Reset(); // キューをクリア
    m_cmdList->Reset(m_cmdAllocator.Get(), nullptr); // 再びコマンドリストをためる準備
}
void DxSurface::waitSync()
{
    if (!m_fenceEvent) {
        m_fenceVal = 1;
        m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    }
    const UINT64 fence = m_fenceVal;
    m_cmdQueue->Signal(m_fence.Get(), fence);
    m_fenceVal++;

    // Wait until the previous frame is finished.
    if (m_fence->GetCompletedValue() < fence) {
        m_fence->SetEventOnCompletion(fence, m_fenceEvent);
        WaitForSingleObject(m_fenceEvent, INFINITE);
    }
}
void DxSurface::present()
{
    m_swapChain->Present(1, 0);
}
// private
ComPtr<ID3D12CommandAllocator> DxSurface::newCommandAllocator(ComPtr<ID3D12Device> device)
{
    ComPtr<ID3D12CommandAllocator> ret;
    if (FAILED(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
            IID_PPV_ARGS(ret.ReleaseAndGetAddressOf())))) {
        throw std::runtime_error("failed CreateCommandAllocator()");
    }
    return ret;
}
ComPtr<ID3D12GraphicsCommandList> DxSurface::newCommandList(ComPtr<ID3D12Device> device, ComPtr<ID3D12CommandAllocator> allocator)
{
    ComPtr<ID3D12GraphicsCommandList> ret;
    if (FAILED(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator.Get(),
            nullptr, IID_PPV_ARGS(ret.ReleaseAndGetAddressOf())))) {
        throw std::runtime_error("failed CreateCommandList()");
    }
    return ret;
}
ComPtr<ID3D12CommandQueue> DxSurface::newCommandQueue(ComPtr<ID3D12Device> device)
{
    ComPtr<ID3D12CommandQueue> ret;
    D3D12_COMMAND_QUEUE_DESC desc = {};
    desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    desc.NodeMask = 0;
    desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    if (FAILED(device->CreateCommandQueue(&desc, IID_PPV_ARGS(ret.ReleaseAndGetAddressOf())))) {
        throw std::runtime_error("failed CreateCommandQueue()");
    }
    return ret;
}
ComPtr<IDXGISwapChain4> DxSurface::newSwapChain(ComPtr<ID3D12Device> device, ComPtr<ID3D12CommandQueue> queue, const Window::Instance& window)
{
    ComPtr<IDXGISwapChain4> ret;
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
    ComPtr<IDXGIFactory6> dxgiFactory = std::static_pointer_cast<DxGraphicsDriver>(Engine::getInstance()->getGraphicsDriver())->getDXGIFactory();
    if (FAILED(dxgiFactory->CreateSwapChainForHwnd(
            queue.Get(), getWin32Window(window->getNativeWindow()), &swapchainDesc, nullptr, nullptr,
            (IDXGISwapChain1**)ret.ReleaseAndGetAddressOf()))) {
        throw std::runtime_error("failed CreateSwapChainForHwnd()");
    }
    return ret;
}
ComPtr<ID3D12DescriptorHeap> DxSurface::newRenderTargetViewHeap(ComPtr<ID3D12Device> device)
{
    ComPtr<ID3D12DescriptorHeap> ret;
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
    desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    desc.NodeMask = 0;
    desc.NumDescriptors = 2;
    desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    if (FAILED(device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(ret.ReleaseAndGetAddressOf())))) {
        throw std::runtime_error("failed CreateDescriptorHeap()");
    }
    return ret;
}
std::vector<ComPtr<ID3D12Resource>> DxSurface::newRenderTargetView(ComPtr<ID3D12Device> device, ComPtr<IDXGISwapChain4> swapChain, ComPtr<ID3D12DescriptorHeap> descHeap)
{
    std::vector<ComPtr<ID3D12Resource>> ret;
    DXGI_SWAP_CHAIN_DESC swcDesc = {};
    if (FAILED(swapChain->GetDesc(&swcDesc))) {
        throw std::runtime_error("failed GetDesc()");
    }
    D3D12_CPU_DESCRIPTOR_HANDLE handle = descHeap->GetCPUDescriptorHandleForHeapStart();
    for (size_t i = 0; i < swcDesc.BufferCount; ++i) {
        ret.push_back(nullptr);
        if (FAILED(swapChain->GetBuffer(static_cast<UINT>(i),
                IID_PPV_ARGS(ret.at(i).ReleaseAndGetAddressOf())))) {
            throw std::runtime_error("failed GetBuffer()");
        }
        device->CreateRenderTargetView(ret.at(i).Get(), nullptr, handle);
        ret.at(i).Get()->SetName(L"RenderTarget");
        handle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    }
    return ret;
}
ComPtr<ID3D12Fence> DxSurface::newFence(ComPtr<ID3D12Device> device, UINT fenceVal)
{
    ComPtr<ID3D12Fence> ret;
    if (FAILED(device->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE,
            IID_PPV_ARGS(ret.ReleaseAndGetAddressOf())))) {
        throw std::runtime_error("failed CreateFence()");
    }
    return ret;
}

ComPtr<ID3D12Resource> DxSurface::newDepthBuffer(ComPtr<ID3D12Device> device, const Window::Instance& window)
{
    D3D12_RESOURCE_DESC depthResDesc = {};
    depthResDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    depthResDesc.Width = window->getWidth();
    depthResDesc.Height = window->getHeight();
    depthResDesc.DepthOrArraySize = 1;
    depthResDesc.Format = DXGI_FORMAT_D32_FLOAT;
    depthResDesc.SampleDesc.Count = 1;
    depthResDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
    D3D12_HEAP_PROPERTIES depthHeapProps = {};
    depthHeapProps.Type = D3D12_HEAP_TYPE_DEFAULT;
    depthHeapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    depthHeapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    D3D12_CLEAR_VALUE depthClearValue = {};
    depthClearValue.DepthStencil.Depth = 1.0f;
    depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;
    ComPtr<ID3D12Resource> depthBuffer = nullptr;
    if (FAILED(device->CreateCommittedResource(&depthHeapProps, D3D12_HEAP_FLAG_NONE, &depthResDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &depthClearValue, IID_PPV_ARGS(depthBuffer.ReleaseAndGetAddressOf())))) {
        throw std::runtime_error("failed CreateCommittedResource()");
    }
    depthBuffer->SetName(L"DepthBuffer");
    return depthBuffer;
}
ComPtr<ID3D12DescriptorHeap> DxSurface::newDepthStencilViewHeap(ComPtr<ID3D12Device> device)
{
    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
    dsvHeapDesc.NumDescriptors = 1;
    dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    ComPtr<ID3D12DescriptorHeap> dsvHeap = nullptr;
    if (FAILED(device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(dsvHeap.ReleaseAndGetAddressOf())))) {
        throw std::runtime_error("failed CreateDescriptorHeap()");
    }
    return dsvHeap;
}
void DxSurface::newDepthStencilView(ComPtr<ID3D12Device> device, ComPtr<ID3D12Resource> depthBuffer, ComPtr<ID3D12DescriptorHeap> descHeap)
{
    D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
    dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
    dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
    dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
    device->CreateDepthStencilView(depthBuffer.Get(), &dsvDesc, descHeap->GetCPUDescriptorHandleForHeapStart());
}
void DxSurface::command(const DxPso::Instance& pso, const std::shared_ptr<DxBuffer> vertex, const std::shared_ptr<DxBuffer> index)
{
    pso->command(m_cmdList.Get());
    int vc = pso->getVertexComponent();
    unsigned int stride = 0;
    if (vc == 2) {
        if (pso->isUsingTexCoord()) {
            stride = sizeof(VertexData2D);
        } else {
            stride = sizeof(glm::vec2);
        }
    } else if (vc == 3) {
        if (pso->isUsingTexCoord()) {
            stride = sizeof(VertexData3D);
        } else {
            stride = sizeof(glm::vec3);
        }
    }
    D3D12_VERTEX_BUFFER_VIEW vbView = vertex->vertexView(stride);
    m_cmdList->IASetVertexBuffers(0, 1, &vbView);
    if (index) {
        D3D12_INDEX_BUFFER_VIEW ibView = index->indexView();
        m_cmdList->IASetIndexBuffer(&ibView);
    }
}
}

#endif