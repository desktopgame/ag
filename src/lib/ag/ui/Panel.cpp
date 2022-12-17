#include <ag/ui/Panel.hpp>

namespace agui {
Panel::Panel(const ILayoutManager::Instance& layoutManager)
    : Container()
{
    setPreferredSize({ 10, 10 });
    setLayoutManager(layoutManager);
}
}