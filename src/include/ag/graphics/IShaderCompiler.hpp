#pragma once
#include <memory>
#include <string>

namespace ag {
class IShader;
class IShaderCompiler {
    using Instance = std::shared_ptr<IShaderCompiler>;
    IShaderCompiler() = default;
    virtual ~IShaderCompiler() = default;

    virtual std::shared_ptr<IShader> compileFromSource(const std::string& source) = 0;
    virtual bool isCompilableFromSource() const = 0;

    virtual std::shared_ptr<IShader> compileFromFile(const std::string& file) = 0;
    virtual bool isCompilableFromFile() const = 0;
};
}