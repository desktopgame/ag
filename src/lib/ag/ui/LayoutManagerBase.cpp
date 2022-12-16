#include <ag/ui/LayoutManagerBase.hpp>
#include <algorithm>

namespace agui {
LayoutManagerBase::LayoutManagerBase()
    : m_elements()
{
}

void LayoutManagerBase::addLayoutComponent(const std::shared_ptr<Component>& c, const std::shared_ptr<LayoutParameter>& param)
{
    m_elements.push_back(LayoutElement { c, param });
}
void LayoutManagerBase::removeLayoutComponent(const std::shared_ptr<Component>& c)
{
    auto iter = std::remove_if(m_elements.begin(), m_elements.end(), [c](auto e) -> bool {
        return e == c;
    });
    m_elements.erase(iter, m_elements.end());
}
}