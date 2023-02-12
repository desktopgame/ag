!include DX_ColorInclude.hlsl
cbuffer cbuff0 : register(b0) { matrix mat; }
cbuffer cbuff1 : register(b1) { float4 color; }

Output BasicVS(float2 pos : POSITION) {
    Output output;
    output.svpos = mul(mat, float4(pos, 0, 1));
    output.color = color;
    return output;
}