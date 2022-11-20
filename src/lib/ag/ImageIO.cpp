#include <ag/ImageIO.hpp>
#include <ag/native/freeimage.hpp>

namespace ag {
bool ImageIO::s_initialized = false;

void ImageIO::initialize()
{
    if (!s_initialized) {
        s_initialized = true;
        FreeImage_Initialise();
    }
}

void ImageIO::destroy()
{
    if (s_initialized) {
        s_initialized = false;
        FreeImage_DeInitialise();
    }
}
}