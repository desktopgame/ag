#pragma once
#include <ag/graphics/IGraphicsDriver.hpp>

namespace ag {
class MtlGraphicsDriver : public IGraphicsDriver {
public:
    explicit MtlGraphicsDriver();
    void useWindowHint();
    void useContextExtension();

private:
};
}