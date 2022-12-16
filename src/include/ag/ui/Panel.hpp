#pragma once
#include <ag/ui/Container.hpp>
#include <ag/ui/ILayoutManager.hpp>

namespace agui {
class Panel : public Container {
public:
    explicit Panel(const ILayoutManager::Instance& layoutManager);
};
}