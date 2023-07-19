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
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float) 0.0f;
    color = albedoTexture.Sample(pointSampler, In.UV);
	
    if (color.a <= 0.0f)
    {
        discard;
    }
    
    return color;
}
// CatPattern
float4 Select_catpattern(VSOut In) : SV_TARGET
{        
    float4 color = (float) 0.0f;
    float2 uv = In.UV;
    uv.y += Time.y / 5.0;
    color = albedoTexture.Sample(pointSampler, uv);
    
    return color;
}

// Lobby_Space1
float4 lobby_space1(VSOut In) : SV_TARGET
{
    float4 color = (float) 0.0f;
    float2 uv = In.UV;
    uv.x += Time.y / 8.0;
    uv.y += -Time.y / 8.0;
    color = albedoTexture.Sample(pointSampler, uv);
    
    return color;
}

// Lobby_Space2
float4 lobby_space2(VSOut In) : SV_TARGET
{
    float4 color = (float) 0.0f;
    float2 uv = In.UV;
    uv.x += Time.y / 10.0;
    uv.y += -Time.y / 10.0;
    color = albedoTexture.Sample(pointSampler, uv);
    
    return color;
}

float4 Tile(VSOut In) : SV_TARGET
{
    float4 color = (0.0f, 0.0f, 0.0f, 1.0f);
    float2 startuv;
    float2 enduv;
    startuv.x = (float) (TileIndex % 10) / 10.0f;
    startuv.y = (float) (TileIndex / 10) / 10.0f;
    enduv = startuv + 0.1f;
    
    float2 finaluv = In.UV * (enduv - startuv) + startuv;
    
    color = albedoTexture.Sample(pointSampler, finaluv);
    
    
    return color;
}