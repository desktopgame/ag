#include <ag/graphics/mtl/MtlShader.hpp>
#ifdef AG_METAL

namespace ag {

MtlShader::MtlShader() { }
MtlShader::~MtlShader() { }
void MtlShader::apply(const std::shared_ptr<ShaderParameter>& parameter) { }
}
#endif