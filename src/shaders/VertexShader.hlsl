struct VIn
{
    float3 position : POSITION;
    float4 colour : COLOR;
};

struct VOut
{
    float4 position : SV_Position;
    float4 colour : COLOR;
};

cbuffer CBuffer0
{
    matrix WVP; // 64 bytes
    //float3 pos;     // 12 bytes
    //float packing;  // 4 bytes (no overlap on 16 byte boundary)
    //float4 col;     // 16 bytes
};

VOut main(VIn input)
{
    VOut output;
    output.position = mul(WVP, float4(input.position, 1));
    output.colour = input.colour;
	return output;
}

