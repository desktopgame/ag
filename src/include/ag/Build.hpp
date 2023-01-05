#pragma once

namespace ag {
class Build {
public:
    static bool isBuiltOnOpenGL();
    static bool isBuiltOnMetal();
    static bool isBuiltOnDirectX();
    static bool isBuiltOnVulkan();

private:
    Build() = delete;
    ~Build() = delete;
};
}