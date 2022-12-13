#pragma once

namespace ag {
class OglShaderLayout {
public:
    static inline constexpr const char* k_attribVertexName = "aVertex";
    static inline constexpr const char* k_attribTexCoordName = "aTexCoord";
    static inline constexpr const char* k_uniformTransformName = "uTransformMatrix";
    static inline constexpr const char* k_uniformTextureName = "uTexture";
    static inline constexpr const char* k_uniformColor1Name = "uColor1";
    static inline constexpr const char* k_uniformColor2Name = "uColor2";
    static inline constexpr int k_attribVertexIndex = 0;
    static inline constexpr int k_attribTexCoordIndex = 1;

private:
    OglShaderLayout() = delete;
    ~OglShaderLayout() = delete;
};
}