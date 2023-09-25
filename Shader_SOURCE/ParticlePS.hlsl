#include "globals.hlsli"



struct GSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    float4 Color : COLOR;
    uint Instance : SV_InstanceID;
};

float4 main(GSOut In) : SV_TARGET
{
    uint id = In.Instance;
    float4 color = { 0.0f, 0.0f, 0.0f, 0.0f };
    float2 uv = In.UV;
    color = albedoTexture.Sample(anisotropicSampler, uv);
    color *= particles[id].curColor;

    if (color.a <= 0.0f)
        discard;
        
    return color;

}