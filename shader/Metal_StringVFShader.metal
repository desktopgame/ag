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