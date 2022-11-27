#pragma once
#include <string>

namespace ag {
namespace internal {
    static constexpr inline const char* GL_ColorVertexShader = R"(
        #version 120
        attribute vec2 aVertex;
        uniform mat4 uTransformMatrix;

        void main(void) {
            gl_Position = uTransformMatrix * vec4(aVertex, 0, 1);
        }
    )";
    static constexpr inline const char* GL_ColorFragmentShader = R"(
        #version 120
        uniform vec4 uColor1;

        void main() {
            gl_FragColor = uColor1;
        }
    )";
    static constexpr inline const char* GL_TextureVertexShader = R"(
        #version 120
        attribute vec2 aVertex;
        attribute vec2 aTexCoord;
        uniform mat4 uTransformMatrix;
        varying vec2 fragTexCoord;

        void main(void) {
            fragTexCoord = aTexCoord;
            gl_Position = uTransformMatrix * vec4(aVertex, 0, 1);
        }
    )";
    static constexpr inline const char* GL_TextureFragmentShader = R"(
        #version 120
        uniform sampler2D uTexture;
        varying vec2 fragTexCoord;

        void main() {
            gl_FragColor = texture2D(uTexture, fragTexCoord);
        }
    )";
    static constexpr inline const char* Metal_ColorVFShader = R"(
        #include <metal_stdlib>
        #include <simd/simd.h>
        using namespace metal;

        typedef struct {
            float4 position [[position]];
        } RasterizerData;

        vertex RasterizerData vertexShader(
           uint vertexID [[vertex_id]],
           device const float2 *vertices
                [[buffer(0)]],
           device const simd::float4x4& transformMatrix
                [[buffer(1)]])
        {
            RasterizerData result = {};
        	result.position = transformMatrix * float4(vertices[vertexID], 0, 1);
            return result;
        }

        fragment float4 fragmentShader(
            RasterizerData in [[stage_in]],
            device const simd::float4& color
                [[buffer(2)]])
        {
            return color;
        }
    )";
}
}