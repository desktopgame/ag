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

std::shared_ptr<DxGraphicsDevice> DxSurface::getDevice()
{
    return std::static_pointer_cast<DxGraphicsDevice>(Engine::getInstance()->getGraphicsDriver()->getGraphicsDevice());
}
}