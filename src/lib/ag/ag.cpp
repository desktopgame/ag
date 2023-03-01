#include <ag/ag.hpp>
#include <iostream>

namespace ag {
void hello()
{
    std::cout << "Hello, ag!" << std::endl;
#ifdef AG_OPEN_GL
    std::cout << " #AG_OPEN_GL=" << AG_OPEN_GL << std::endl;
#endif
#ifdef AG_METAL
    std::cout << " #AG_METAL=" << AG_METAL << std::endl;
#endif
#ifdef AG_DIRECT_X
    std::cout << " #AG_DIRECT_X=" << AG_DIRECT_X << std::endl;
#endif
}
} // namespace ag