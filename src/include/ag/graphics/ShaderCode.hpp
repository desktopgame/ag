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
        uniform vec4 uColor;

        void main() {
            gl_FragColor = uColor;
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
        uniform vec4 uColor;
        varying vec2 fragTexCoord;

        void main() {
            gl_FragColor = texture2D(uTexture, fragTexCoord) * uColor;
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
        uniform vec4 uColor;

        void main() {
            vec4 col = uColor;
            col.a = texture2D(uTexture, fragTexCoord).a;
            gl_FragColor = col;
        }
    )";
    static constexpr inline const char* GL_ModelColorNoLightVertexShader = R"(
        #version 120
        attribute vec3 aVertex;
        uniform mat4 uTransformMatrix;

        void main(void) {
            gl_Position = uTransformMatrix * vec4(aVertex, 1);
        }
    )";
    static constexpr inline const char* GL_ModelColorNoLightFragmentShader = R"(
        #version 120
        uniform vec4 uColor;

        void main() {
            gl_FragColor = uColor;
        }
    )";
    static constexpr inline const char* GL_ModelTextureNoLightVertexShader = R"(
        #version 120
        attribute vec3 aVertex;
        attribute vec2 aTexCoord;
        uniform mat4 uTransformMatrix;
        varying vec2 fragTexCoord;

        void main(void) {
            fragTexCoord = aTexCoord;
            gl_Position = uTransformMatrix * vec4(aVertex, 1);
        }
    )";
    static constexpr inline const char* GL_ModelTextureNoLightFragmentShader = R"(
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
           device const packed_float2 *vertices
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
            packed_float2 position;
            packed_float2 texcoord;
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
            packed_float2 position;
            packed_float2 texcoord;
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
    static constexpr inline const char* Metal_ModelColorNoLightVFShader = R"(
        #include <metal_stdlib>
        #include <simd/simd.h>
        using namespace metal;

        typedef struct {
            float4 position [[position]];
        } RasterizerData;

        vertex RasterizerData vertexShader(
           uint vertexID [[vertex_id]],
           device const packed_float3 *vertices
                [[buffer(0)]],
           device const simd::float4x4& transformMatrix
                [[buffer(1)]])
        {
            RasterizerData result = {};
        	result.position = transformMatrix * float4(vertices[vertexID], 1);
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
    static constexpr inline const char* Metal_ModelTextureNoLightVFShader = R"(
        #include <metal_stdlib>
        #include <simd/simd.h>
        using namespace metal;

        typedef struct {
            packed_float3 position;
            packed_float2 texcoord;
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
        	result.position = transformMatrix * float4(vd.position, 1);
            result.texcoord = vd.texcoord;
            return result;
        }

        fragment half4 fragmentShader(
            RasterizerData in [[stage_in]],
            texture2d<half, access::sample> tex
                [[texture(10)]])
        {
            constexpr sampler s(address::repeat, filter::linear);
            return (half4)tex.sample(s, in.texcoord);
        }
    )";
    static constexpr inline const char* DX_ColorVertexShader = R"(
        struct Output {
            float4 svpos : SV_POSITION;
            float4 color : COLOR;
        };
        cbuffer cbuff0 : register(b0) { matrix mat; }
        cbuffer cbuff1 : register(b1) { float4 color; }

        Output BasicVS(float2 pos : POSITION) {
            Output output;
            output.svpos = mul(mat, float4(pos, 0, 1));
            output.color = color;
            return output;
        }
    )";
    static constexpr inline const char* DX_ColorFragmentShader = R"(
        struct Output {
            float4 svpos : SV_POSITION;
            float4 color : COLOR;
        };

        float4 BasicPS(Output input) : SV_TARGET {
            return input.color;
        }
    )";
}
}
