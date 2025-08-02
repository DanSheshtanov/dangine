#include "Common.hlsli"


struct VOut
{
    float4 position : SV_Position;
    float4 colour : COLOR;
    float2 uv : TEXCOORD;
};

cbuffer CBuffer
{
    float waveSpeed;
    float3 padding;
};

VOut main(VIn input)
{
    VOut output;
    float scale = (sin(input.position.x * 10 + time * waveSpeed) / 2.0) + 1;
    output.position = mul(WVP, float4(input.position, 1));
    output.position.y += scale;
    output.colour = float4(1, 1, 1, 1);
    output.uv = input.uv;
    return output;
}

