#include <ag/graphics/ogl/OglGraphicsDriver.hpp>

namespace ag {
OglGraphicsDriver::OglGraphicsDriver()
    : m_device(std::make_shared<OglGraphicsDevice>())
{
}

void OglGraphicsDriver::useWindowHint()
{
}

void OglGraphicsDriver::useContextExtension()
{
}
std::shared_ptr<IGraphicsDevice> OglGraphicsDriver::getGraphicsDevice() const
{
    return m_device;
}
}