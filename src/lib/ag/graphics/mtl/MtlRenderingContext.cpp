#include <ag/graphics/mtl/MtlRenderingContext.hpp>

namespace ag {
MtlRenderingContext::MtlRenderingContext() { }
MtlRenderingContext::~MtlRenderingContext() { }
void MtlRenderingContext::setup(const std::shared_ptr<IShader>& shader) { }
void MtlRenderingContext::teardown(const std::shared_ptr<IShader>& shader) { }
}