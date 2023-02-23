!include DX_StringInclude.hlsl

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 BasicPS(Output input) : SV_TARGET {
    float4 col = input.color;
    col.a = float4(tex.Sample(smp, input.uv)).a;
    return col;
}