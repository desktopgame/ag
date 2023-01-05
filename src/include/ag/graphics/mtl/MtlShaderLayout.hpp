#pragma once
#ifdef AG_METAL

namespace ag {
class MtlShaderLayout {
public:
    static inline constexpr int k_vertexIndex = 0;
    static inline constexpr int k_transformIndex = 1;
    static inline constexpr int k_colorIndex = 2;
    static inline constexpr int k_textureIndex = 10;

private:
    MtlShaderLayout() = delete;
    ~MtlShaderLayout() = delete;
};
}
#endif