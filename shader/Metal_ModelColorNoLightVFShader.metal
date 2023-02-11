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