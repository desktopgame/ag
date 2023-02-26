!include DX_ModelTextureNoLightInclude.hlsl
cbuffer cbuff0 : register(b0) { matrix mat; }

Output BasicVS(float3 pos : POSITION, float2 uv : TEXCOORD) {
    Output output;
    output.svpos = mul(mat, float4(pos, 1));
    output.uv = uv;
    return output;
}
