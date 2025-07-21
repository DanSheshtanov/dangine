cbuffer PerFrame : register(b13)
{
    float time; // 4 bytes
    float3 packing; // 12 bytes
}

cbuffer PerObject : register(b12)
{
    matrix WVP; // 64 bytes
}

struct VIn
{
    float3 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};