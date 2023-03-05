#pragma once
#ifdef AG_DIRECT_X
#include <ag/graphics/IRenderFunction.hpp>
#include <ag/graphics/dx/DxPsoPool.hpp>
#include <ag/graphics/dx/DxSurface.hpp>
#include <ag/native/dx.hpp>

namespace ag {
class DxRenderFunction : public IRenderFunction {
public:
    explicit DxRenderFunction();
    void link(const std::shared_ptr<Window>& window) override;
    void begin(const std::shared_ptr<Window>& window, const RenderPass& pass) override;
    void end() override;
    void clear(const std::shared_ptr<Window>& window) override;
    void present(const std::shared_ptr<Window>& window) override;
    void waitSync(const std::shared_ptr<Window>& window) override;

    std::shared_ptr<DxPsoPool> getPsoPool() const;
    std::shared_ptr<DxSurface> getSurface() const;

private:
    std::shared_ptr<DxPsoPool> m_psoPool;
    std::shared_ptr<DxSurface> m_surface;
};
}
#endif