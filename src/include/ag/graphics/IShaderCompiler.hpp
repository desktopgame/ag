#pragma once
#include <memory>
#include <string>

namespace ag {
class IShader;
class IShaderCompiler {
public:
    using Instance = std::shared_ptr<IShaderCompiler>;
    IShaderCompiler() = default;
    virtual ~IShaderCompiler() = default;

    virtual std::shared_ptr<IShader> compileFromPartedSource(const std::string& vSource, const std::string& fSource) = 0;
    virtual bool isCompilableFromPartedSource() const = 0;

    virtual std::shared_ptr<IShader> compileFromSingleSource(const std::string& source) = 0;
    virtual bool isCompilableFromSingleSource() const = 0;

    virtual std::shared_ptr<IShader> compileFromSingleFile(const std::string& file) = 0;
    virtual bool isCompilableFromSingleFile() const = 0;
};
}