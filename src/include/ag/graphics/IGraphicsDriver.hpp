#pragma once
#include <memory>

namespace ag {
class IGraphicsDevice;
class IShaderCompiler;
class IGraphicsDriver {
public:
    IGraphicsDriver() = default;
    virtual ~IGraphicsDriver() = default;
    virtual void useWindowHint() = 0;
    virtual void useContextExtension() = 0;
    virtual std::shared_ptr<IGraphicsDevice> getGraphicsDevice() const = 0;
    virtual std::shared_ptr<IShaderCompiler> getShaderCompiler() const = 0;

private:
};
}