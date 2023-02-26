!include DX_ModelColorNoLightInclude.hlsl
cbuffer cbuff0 : register(b0) { matrix mat; }
cbuffer cbuff1 : register(b1) { float4 color; }

Output BasicVS(float3 pos : POSITION) {
    Output output;
    output.svpos = mul(mat, float4(pos, 1));
    output.color = color;
    return output;
}