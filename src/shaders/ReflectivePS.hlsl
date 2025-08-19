Texture2D texture0 : register(t0);
TextureCube skybox0 : register(t1);
sampler sampler0;

cbuffer CbufferPS
{
    float reflectiveness;
    float3 packing;
};

float4 main(float4 position : SV_Position, float4 colour : COLOR, float2 uv : TEXCOORD0, float3 reflectedUVW : TEXCOORD1) : SV_TARGET
{
    float4 sampled = texture0.Sample(sampler0, float2(uv.x, 1 - uv.y));
    float4 reflectedSampled = skybox0.Sample(sampler0, reflectedUVW);
    float4 combined = ((colour * sampled) * (1.0 - reflectiveness)) + (reflectedSampled * reflectiveness);
    return saturate(combined);
}