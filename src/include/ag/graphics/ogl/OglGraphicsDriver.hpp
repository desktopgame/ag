#pragma once
#include <ag/graphics/IGraphicsDriver.hpp>

namespace ag {
class OglGraphicsDriver : public IGraphicsDriver {
public:
    explicit OglGraphicsDriver();
    void useWindowHint() override;
    void useContextExtension() override;

private:
};
}