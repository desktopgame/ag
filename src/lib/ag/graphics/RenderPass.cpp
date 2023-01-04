#include <ag/graphics/RenderPass.hpp>

namespace ag {
RenderPass::RenderPass()
    : renderMode(RenderMode::Render2D)
{
}

RenderPass RenderPass::default2D()
{
    RenderPass p;
    p.renderMode = RenderMode::Render2D;
    return p;
}
RenderPass RenderPass::default3D()
{
    RenderPass p;
    p.renderMode = RenderMode::Render3D;
    return p;
}
}