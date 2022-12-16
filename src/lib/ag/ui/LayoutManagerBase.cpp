#include <ag/ui/LayoutManagerBase.hpp>

namespace agui {
LayoutManagerBase::LayoutManagerBase()
    : m_paramMap()
{
}

void LayoutManagerBase::addLayoutComponent(const std::shared_ptr<Component>& c, const std::shared_ptr<LayoutParameter>& param)
{
    m_paramMap.insert_or_assign(c, param);
}
void LayoutManagerBase::removeLayoutComponent(const std::shared_ptr<Component>& c)
{
    m_paramMap.erase(c);
}
}