#include "Common.hlsli"


struct VOut
{
    float4 position : SV_Position;
    float4 colour : COLOR;
    float2 uv : TEXCOORD;
};

VOut main(VIn input)
{
    VOut output;
    output.position = mul(WVP, float4(input.position, 1));
    output.colour = float4(1, 1, 1, 1);
    output.uv = input.uv;
    return output;
}

