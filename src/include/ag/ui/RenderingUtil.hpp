#pragma once
#include <ag/graphics/Renderer.hpp>
#include <ag/ui/Rect.hpp>

namespace agui {
class RenderingUtil {
public:
    explicit RenderingUtil(const std::shared_ptr<ag::Renderer>& renderer);
    void fillBorderedRect(const Rect& rect, int thickness, const glm::vec4& bg, const glm::vec4& border);

private:
    std::shared_ptr<ag::Renderer> m_renderer;
};
}