#include <ag/Engine.hpp>
#include <ag/ImageIO.hpp>
#include <cassert>

int main(int argc, char* argv[])
{
    auto engine = ag::Engine::getInstance()->startup(argc, argv);
    ag::Image img;
    bool success = ag::ImageIO::load("testdata/ghicon.png", ag::ImageFormat::PNG, img);
    assert(success);
    assert(img.width == 420);
    assert(img.height == 420);
    return 0;
}