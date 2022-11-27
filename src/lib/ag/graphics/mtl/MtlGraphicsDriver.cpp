#include <ag/graphics/mtl/MtlGraphicsDriver.hpp>
#ifdef AG_METAL
#include <ag/graphics/mtl/MtlGraphicsDevice.hpp>
#include <ag/graphics/mtl/MtlRenderFunction.hpp>
#include <ag/graphics/mtl/MtlShaderCompiler.hpp>
#include <ag/native/glfw.hpp>

namespace ag {
MtlGraphicsDriver::MtlGraphicsDriver()
    : m_nativeDevice(MTL::CreateSystemDefaultDevice())
    , m_renderFunction(std::make_shared<MtlRenderFunction>())
{
    m_device = std::make_shared<MtlGraphicsDevice>(m_nativeDevice);
    m_shaderCompiler = std::make_shared<MtlShaderCompiler>(m_nativeDevice);
}
MtlGraphicsDriver::~MtlGraphicsDriver()
{
    m_nativeDevice->release();
}

void MtlGraphicsDriver::useWindowHint()
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void MtlGraphicsDriver::useContextExtension()
{
}
std::shared_ptr<IGraphicsDevice> MtlGraphicsDriver::getGraphicsDevice() const { return m_device; }
std::shared_ptr<IShaderCompiler> MtlGraphicsDriver::getShaderCompiler() const { return m_shaderCompiler; }
std::shared_ptr<IRenderFunction> MtlGraphicsDriver::getRenderFunction() const { return m_renderFunction; }
void MtlGraphicsDriver::useDevice(CA::MetalLayer* metalLayer)
{
    metalLayer->setDevice(m_nativeDevice);
}
}
#endif