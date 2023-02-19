!include DX_TextureInclude.hlsl

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 BasicPS(Output input) : SV_TARGET {
    float4 col = float4(tex.Sample(smp, input.uv)) * input.color;
    return col;
}