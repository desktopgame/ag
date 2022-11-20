#pragma once

namespace ag {
class ImageIO {
public:
    static void initialize();
    static void destroy();

private:
    ImageIO() = delete;
    ~ImageIO() = delete;
    static bool s_initialized;
};
}