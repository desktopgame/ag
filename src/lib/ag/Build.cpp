#include <ag/Build.hpp>

namespace ag {

bool Build::isBuiltOnOpenGL()
{
#ifdef AG_OPEN_GL
    return true;
#else
    return false;
#endif
}
bool Build::isBuiltOnMetal()
{
#ifdef AG_METAL
    return true;
#else
    return false;
#endif
}
bool Build::isBuiltOnDirectX()
{
    return false;
}
bool Build::isBuiltOnVulkan()
{
    return false;
}
}