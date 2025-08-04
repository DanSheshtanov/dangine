struct DirectionalLight
{
    float4 transposedDirection;
    float4 colour;
};

float3 CalculateDirectionalContribution(DirectionalLight light, float3 vNormal)
{
    float diffuseAmount = dot(light.transposedDirection.xyz, vNormal);
    diffuseAmount = saturate(diffuseAmount);
    return light.colour * diffuseAmount;
}

float3 CalculateAllLighting(float3 ambientColour, DirectionalLight light, float3 vNormal)
{
    return saturate(ambientColour + CalculateDirectionalContribution(light, vNormal));
}