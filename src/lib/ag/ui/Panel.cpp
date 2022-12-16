#include <ag/ui/Panel.hpp>

namespace agui {
Panel::Panel(const ILayoutManager::Instance& layoutManager)
{
    setLayoutManager(layoutManager);
}
}