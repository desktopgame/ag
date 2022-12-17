#include <ag/ui/RenderingUtil.hpp>

namespace agui {
RenderingUtil::RenderingUtil(const std::shared_ptr<ag::Renderer>& renderer)
    : m_renderer(renderer)
{
}
void RenderingUtil::fillBorderedRect(const Rect& rect, int thickness, const glm::vec4& bg, const glm::vec4& border)
{
    const int t_ = thickness;
    m_renderer->fillRect(rect.position, rect.size, bg);
    m_renderer->fillRect(rect.position, { t_, rect.size.y }, border);
    m_renderer->fillRect(rect.position, { rect.size.x, t_ }, border);
    m_renderer->fillRect({ rect.right() - t_, rect.top() }, { t_, rect.size.y }, border);
    m_renderer->fillRect({ rect.left(), rect.bottom() - t_ }, { rect.size.x, t_ }, border);
}
}