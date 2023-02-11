!include DX_ColorInclude.hlsl

float4 BasicPS(Output input) : SV_TARGET {
    return input.color;
}