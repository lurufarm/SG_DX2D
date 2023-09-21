#include "globals.hlsli"

struct GSOut
{
    float4 pos : SV_Position;
    float2 UV : TEXCOORD;
    uint Instance : SV_InstanceID;
};

float4 main(GSOut In) : SV_TARGET
{
    float4 Out = (float4) 0.0f;
    
    Out = albedoTexture.Sample(pointSampler, In.UV);
    
    if (Out.a <= 0.0f)
        discard;
    
    return Out;
}