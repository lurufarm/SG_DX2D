#include "globals.hlsli"

struct GSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    uint Instance : SV_InstanceID;
};

float4 main(GSOut In) : SV_TARGET
{
    uint id = In.Instance;
    float4 color = (float4) 0.0f;
    float2 uv = In.UV;
    color = albedoTexture.Sample(anisotropicSampler, uv);
    if (color.a <= 0.0f)
        discard;
    else
    {
        color.x *= particles[id].color.x;
        color.y *= particles[id].color.y;
        color.z *= particles[id].color.z;
        color.w *= particles[id].color.a;
        color = saturate(color);
    }

    return color;

}