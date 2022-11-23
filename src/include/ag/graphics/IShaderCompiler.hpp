#pragma once
#include <memory>
#include <string>

namespace ag {
class IShader;
class IShaderCompiler {
    using Instance = std::shared_ptr<IShaderCompiler>;
    IShaderCompiler() = default;
    virtual ~IShaderCompiler() = default;

    virtual std::shared_ptr<IShader> compileFromSource(const std::string& vSource, const std::string& fSource) = 0;
    virtual bool isCompilableFromSource() const = 0;

    virtual std::shared_ptr<IShader> compileFromSingleFile(const std::string& file) = 0;
    virtual bool isCompilableFromSingleFile() const = 0;
};
}