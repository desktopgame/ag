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
        uniform vec4 uColor1;
        varying vec2 fragTexCoord;

        void main() {
            gl_FragColor = texture2D(uTexture, fragTexCoord) * uColor1;
        }
    )";
    static constexpr inline const char* GL_StringVertexShader = R"(
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
    static constexpr inline const char* GL_StringFragmentShader = R"(
        #version 120
        uniform sampler2D uTexture;
        varying vec2 fragTexCoord;
        uniform vec4 uColor1;

        void main() {
            vec4 col = uColor1;
            col.a = texture2D(uTexture, fragTexCoord).a;
            gl_FragColor = col;
        }
    )";
    static constexpr inline const char* GL_ModelVertexShader = R"(
        #version 120
        attribute vec3 aVertex;
        uniform mat4 uTransformMatrix;

        void main(void) {
            gl_Position = uTransformMatrix * vec4(aVertex, 1);
        }
    )";
    static constexpr inline const char* GL_ModelFragmentShader = R"(
        #version 120

        void main() {
            gl_FragColor = vec4(1, 0, 0, 1);
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
    static constexpr inline const char* Metal_TextureVFShader = R"(
        #include <metal_stdlib>
        #include <simd/simd.h>
        using namespace metal;

        typedef struct {
            float2 position;
            float2 texcoord;
        } VertexData;

        typedef struct {
            float4 position [[position]];
            float2 texcoord;
        } RasterizerData;

        vertex RasterizerData vertexShader(
           uint vertexID [[vertex_id]],
           device const VertexData *vertices
                [[buffer(0)]],
           device const simd::float4x4& transformMatrix
                [[buffer(1)]])
        {
            const device VertexData& vd = vertices[vertexID];
            RasterizerData result = {};
        	result.position = transformMatrix * float4(vd.position, 0, 1);
            result.texcoord = vd.texcoord;
            return result;
        }

        fragment half4 fragmentShader(
            RasterizerData in [[stage_in]],
            texture2d<half, access::sample> tex
                [[texture(10)]],
            device const simd::float4& color
                [[buffer(2)]])
        {
            constexpr sampler s(address::repeat, filter::linear);
            return tex.sample(s, in.texcoord).rgba * (half4)color;
        }
    )";
    static constexpr inline const char* Metal_StringVFShader = R"(
        #include <metal_stdlib>
        #include <simd/simd.h>
        using namespace metal;

        typedef struct {
            float2 position;
            float2 texcoord;
        } VertexData;

        typedef struct {
            float4 position [[position]];
            float2 texcoord;
        } RasterizerData;

        vertex RasterizerData vertexShader(
           uint vertexID [[vertex_id]],
           device const VertexData *vertices
                [[buffer(0)]],
           device const simd::float4x4& transformMatrix
                [[buffer(1)]])
        {
            const device VertexData& vd = vertices[vertexID];
            RasterizerData result = {};
        	result.position = transformMatrix * float4(vd.position, 0, 1);
            result.texcoord = vd.texcoord;
            return result;
        }

        fragment half4 fragmentShader(
            RasterizerData in [[stage_in]],
            texture2d<half, access::sample> tex
                [[texture(10)]],
            device const simd::float4& color
                [[buffer(2)]])
        {
            constexpr sampler s(address::repeat, filter::linear);
            half4 hcolor = (half4)color;
            hcolor.a = tex.sample(s, in.texcoord).a;
            return hcolor;
        }
    )";
}
}