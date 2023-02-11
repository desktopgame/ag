struct Output {
    float4 svpos : SV_POSITION;
    float4 color : COLOR;
};

float4 BasicPS(Output input) : SV_TARGET {
    return input.color;
}