#include "Common.hlsli"


struct VOut
{
    float4 position : SV_Position;
    float4 colour : COLOR;
    float2 uv : TEXCOORD;
};

//cbuffer CBuffer0 : register(b0)
//{
//    float time;    // 12 bytes
//    float3 packing;  // 4 bytes (no overlap on 16 byte boundary)
//    //float4 col;     // 16 bytes
//};



VOut main(VIn input)
{
    VOut output;
    //output.position = mul(WVP, float4(input.position, 1));
    float scale = (sin(input.position.x * 10 + time) / 2.0) + 1;
    output.position = mul(WVP, float4(input.position, 1));
    output.position.y += scale;
    output.colour = float4(1, 1, 1, 1);
    output.uv = input.uv;
    return output;
}

