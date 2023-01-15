#pragma once
#ifdef AG_DIRECT_X
#include <ag/Window.hpp>
#include <ag/graphics/dx/DxGraphicsDevice.hpp>
#include <ag/native/dx.hpp>
#include <memory>
#include <vector>

namespace ag {
class DxSurface {
public:
    using Instance = std::shared_ptr<Window>;
    explicit DxSurface(const Window::Instance& window);

    void transitionPresentToRender();
    void transitionRenderToPresent();
    void clear(const glm::vec3& color);
    void execute();
    void reset();
    void waitSync();
    void present();

private:
    static std::shared_ptr<DxGraphicsDevice> getDevice();
    ID3D12CommandAllocator* m_cmdAllocator;
    ID3D12GraphicsCommandList* m_cmdList;
    ID3D12CommandQueue* m_cmdQueue;
    IDXGISwapChain4* m_swapChain;
    ID3D12DescriptorHeap* m_rtvHeap;
    std::vector<ID3D12Resource*> m_backBuffers;
    ID3D12Fence* m_fence;
    UINT m_fenceVal;
};
}
#endif