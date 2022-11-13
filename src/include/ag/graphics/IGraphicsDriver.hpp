#pragma once
namespace ag {
class IGraphicsDriver {
public:
    IGraphicsDriver() = default;
    virtual ~IGraphicsDriver() = default;
    virtual void useWindowHint() = 0;
    virtual void useContextExtension() = 0;

private:
};
}