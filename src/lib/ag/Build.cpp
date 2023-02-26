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
#ifdef AG_DIRECT_X
    return true;
#else
    return false;
#endif
}
bool isBuiltOnVulkan()
{
    return false;
}
}