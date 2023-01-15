#ifdef AG_DIRECT_X
#include <ag/Engine.hpp>
#include <ag/graphics/IGraphicsDevice.hpp>
#include <ag/graphics/IGraphicsDriver.hpp>
#include <ag/graphics/dx/DxGraphicsDriver.hpp>
#include <ag/graphics/dx/DxSurface.hpp>

namespace ag {
DxSurface::DxSurface(const Window::Instance& window)
    : m_cmdAllocator(nullptr)
    , m_cmdList(nullptr)
    , m_cmdQueue(nullptr)
    , m_swapChain(nullptr)
    , m_rtvHeap(nullptr)
    , m_backBuffers()
    , m_fence(nullptr)
    , m_fenceVal(0)
{
    m_cmdAllocator = getDevice()->newCommandAllocator();
    m_cmdList = getDevice()->newCommandList(m_cmdAllocator);
    m_cmdQueue = getDevice()->newCommandQueue();
    m_swapChain = getDevice()->newSwapChain(m_cmdQueue, window);
    m_rtvHeap = getDevice()->newRenderTargetViewHeap();
    m_backBuffers = getDevice()->newRenderTargetView(m_swapChain, m_rtvHeap);
    m_fence = getDevice()->newFence(0);
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
    rtvH.ptr += static_cast<ULONG_PTR>(bbIdx * getDevice()->GetRenderTargetViewHeapIncrementSize());
    m_cmdList->OMSetRenderTargets(1, &rtvH, false, nullptr);

    // 画面クリア
    float clearColor[] = { 1.0f, 1.0f, 0.0f, 1.0f }; // 黄色
    m_cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
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
std::shared_ptr<DxGraphicsDevice> DxSurface::getDevice()
{
    return std::static_pointer_cast<DxGraphicsDevice>(Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice());
}
}
#endif