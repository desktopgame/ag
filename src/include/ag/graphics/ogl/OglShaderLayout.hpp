#pragma once
#ifdef AG_OPEN_GL

namespace ag {
class OglShaderLayout {
public:
    static inline constexpr const char* k_attribVertexName = "aVertex";
    static inline constexpr const char* k_attribTexCoordName = "aTexCoord";
    static inline constexpr const char* k_uniformTransformName = "uTransformMatrix";
    static inline constexpr const char* k_uniformTextureName = "uTexture";
    static inline constexpr const char* k_uniformColorName = "uColor";
    static inline constexpr int k_attribVertexIndex = 0;
    static inline constexpr int k_attribTexCoordIndex = 1;

private:
    OglShaderLayout() = delete;
    ~OglShaderLayout() = delete;
};
}
#endif