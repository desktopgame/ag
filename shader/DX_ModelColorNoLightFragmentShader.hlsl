!include DX_ModelColorNoLightInclude.hlsl

float4 BasicPS(Output input) : SV_TARGET {
    return input.color;
}