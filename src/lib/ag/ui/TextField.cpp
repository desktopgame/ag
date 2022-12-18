#include <ag/ui/MouseEvent.hpp>
#include <ag/ui/RenderingUtil.hpp>
#include <ag/ui/TextField.hpp>

namespace agui {
TextField::TextField()
    : Component()
    , m_focusOn(false)
{
    setPreferredSize({ 200, 20 });
}

void TextField::profile()
{
}
void TextField::update(const std::shared_ptr<ag::Renderer>& r)
{
    RenderingUtil util { r };
    const glm::vec4 buttonBack = m_focusOn ? glm::vec4 { 0.2f, 0.2f, 0.2f, 1.f } : glm::vec4 { 0.1f, 0.1f, 0.1f, 1.f };
    const glm::vec4 buttonEdge = { 0.f, 0.f, 0.f, 1.f };
    util.fillBorderedRect(getBounds(), k_edgeThickness, buttonBack, buttonEdge);
}
// protected
void TextField::processMouseEvent(const std::shared_ptr<MouseEvent>& e)
{
    if (e->action == MouseAction::Press) {
        m_focusOn = getBounds().contains(e->position);
    }
}
}