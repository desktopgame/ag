#pragma once

namespace ag {
enum class RenderMode {
    Render2D,
    Render3D
};
class RenderPass {
public:
    explicit RenderPass();
    RenderMode renderMode;

private:
};
}