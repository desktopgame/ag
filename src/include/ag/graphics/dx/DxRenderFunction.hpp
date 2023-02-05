#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/IRenderFunction.hpp>
#include <ag/graphics/dx/DxPsoCache.hpp>
#include <ag/graphics/dx/DxSurface.hpp>
#include <ag/native/dx.hpp>


namespace ag {
class DxRenderFunction : public IRenderFunction {
public:
    explicit DxRenderFunction(ID3D12Device* device);
    void link(const std::shared_ptr<Window>& window) override;
    void begin(const std::shared_ptr<Window>& window, const RenderPass& pass) override;
    void end() override;
    void clear(const std::shared_ptr<Window>& window) override;
    void present(const std::shared_ptr<Window>& window) override;

    std::shared_ptr<DxPsoCache> getPsoCache() const;
    std::shared_ptr<DxSurface> getSurface() const;

private:
    std::shared_ptr<DxPsoCache> m_psoCache;
    std::shared_ptr<DxSurface> m_surface;
};
}
#endif