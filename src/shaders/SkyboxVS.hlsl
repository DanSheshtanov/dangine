#include "Common.hlsli"

struct VOut
{
    float4 position : SV_Position;
    float4 colour : COLOR;
    float3 uvw : TEXCOORD;
};

VOut main( VIn input )
{
    VOut output;
    
    // Position
    output.position = mul(WVP, float4(input.position, 1));
    // Texture coords
    output.uvw = input.position.xyz;
    
    //output.colour = input.colour;
    output.colour = float4(1, 1, 1, 1);
    
	return output;
}