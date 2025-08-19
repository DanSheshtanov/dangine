#include "Common.hlsli"
#include "Lighting.hlsli"

//struct PointLight
//{
//    float4 position; // 16 bytes
    
//    float4 colour; // 16 bytes
    
//    float strength; // 4 bytes
//    bool enabled; // 4 bytes
//    float2 padding; // 8 bytes
//};

struct VOut
{
    float4 position : SV_Position;
    float4 colour : COLOR;
    float2 uv : TEXCOORD0;
    float3 uvw : TEXCOORD1;
};

cbuffer LightingData
{
    float4 ambientLightCol; // 16 bytes
    DirectionalLight dirLight;
    PointLight pointLights[MAX_POINT_LIGHTS]; // 384 bytes
}

VOut main(VIn input)
{
    //VOut output;
    //output.position = mul(WVP, float4(input.position, 1));
    //output.colour = float4(ambientLight.xyz * ambientLight.z, 1);
    //output.uv = input.uv;
    //return output;
    
    VOut output;
    
    // Position
    output.position = mul(WVP, float4(input.position, 1));
    // Texture coords
    output.uv = input.uv;
    
    // --Point lighting
    //float3 pointFinal = float3(0, 0, 0);
    //for (int i = 0; i < MAX_POINT_LIGHTS; ++i)
    //{
    //    if (!pointLights[i].enabled)
    //        continue;
        
    //    float4 pointLightDir = normalize(pointLights[i].position - input.position);
    //    float pointLightDistance = length(pointLights[i].position - input.position);
    //    float pointLightAttenuation = pointLights[i].strength / (pointLightDistance * pointLightDistance + pointLights[i].strength);
    //    float pointAmount = dot(pointLightDir.xyz, input.norm) * pointLightAttenuation;
    //    pointAmount = saturate(pointAmount);
    //    pointFinal += pointLights[i].colour * pointAmount;
    //}
    
    // Final colour
    //output.colour = saturate(ambientLightCol + float4(directionalFinal, 1)); //+float4(pointFinal, 1));
    output.colour = float4(CalculateAllLighting(ambientLightCol.xyz, dirLight, pointLights, float4(input.position, 1), input.normal), 1);
    
    output.uvw = CalculateReflectionUVW(World, float4(input.position, 1), input.normal, cameraPos);
    
    return output;
}