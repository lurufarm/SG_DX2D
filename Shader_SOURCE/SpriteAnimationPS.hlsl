#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;    

    if (animationType == 1)
    {
        float2 diff = (AtlasSize - SpriteSize) / 2.0f;
        float2 UV = (SpriteLeftTop - diff - SpriteOffset)
                + (AtlasSize * In.UV);
        
        if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
            || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
            discard;
        
        color = atlasTexture.Sample(pointSampler, UV);
    }
    else // 반대 방향의 UV를 출력
    {
        float2 diff = (AtlasSize - SpriteSize) / 2.0f;
        float2 UV = (SpriteLeftTop - diff - SpriteOffset) + float2(AtlasSize.x * (1.0f - In.UV.x), AtlasSize.y * In.UV.y);

        if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
        || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
            discard;

        color = atlasTexture.Sample(pointSampler, UV);
    }

    float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.0f);
    for (int i = 0; i < lightsAttribute[0].pad; i++)
    {
        CalculateLight2D(lightColor, In.WorldPos, i);
    }
    color *= lightColor;

    if (alphaValue == 1)
    {
        if (color.a >= 1.0f)
            color.a = 0.5f;
    }
    
    return color;
}



float4 main2(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;

    if (animationType == 1)
    {
        float2 diff = (AtlasSize - SpriteSize) / 2.0f;
        float2 UV = (SpriteLeftTop - diff - SpriteOffset)
                + (AtlasSize * In.UV);
        
        if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
            || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
            discard;
        
        color = atlasTexture.Sample(pointSampler, UV);
    }
    else // 반대 방향의 UV를 출력
    {
        float2 diff = (AtlasSize - SpriteSize) / 2.0f;
        float2 UV = (SpriteLeftTop - diff - SpriteOffset) + float2(AtlasSize.x * (1.0f - In.UV.x), AtlasSize.y * In.UV.y);

        if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
        || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
            discard;

        color = atlasTexture.Sample(pointSampler, UV);
    }

    float4 lightColor = float4(0.0f, 0.0f, 0.0f, 0.1f);
    for (int i = 0; i < lightsAttribute[0].pad; i++)
    {
        CalculateLight2D(lightColor, In.WorldPos, i);
    }
    
    color.a -= 0.5f;
    color.xyz *= lightColor.xyz;

    
    return color;
}