#include <ag/Build.hpp>

namespace ag {

bool isBuiltOnOpenGL()
{
#ifdef AG_OPEN_GL
    return true;
#else
    return false;
#endif
}
bool isBuiltOnMetal()
{
#ifdef AG_METAL
    return true;
#else
    return false;
#endif
}
bool isBuiltOnDirectX()
{
    return false;
}
bool isBuiltOnVulkan()
{
    return false;
}
}