struct Output {
    float4 svpos : SV_POSITION;
    float4 color : COLOR;
};
cbuffer cbuff0 : register(b0) { matrix mat; }
cbuffer cbuff1 : register(b1) { float4 color; }

Output BasicVS(float4 pos : POSITION) {
    Output output;
    output.svpos = mul(mat, pos);
    output.color = color;
    return output;
}