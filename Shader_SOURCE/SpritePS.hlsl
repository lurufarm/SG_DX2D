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
    float4 color = (float) 0.0f;
    color = albedoTexture.Sample(pointSampler, In.UV);
	
    float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.0f);
       
    for (int i = 0; i < lightsAttribute[0].pad; i++)
    {
 //       CalculateLight2D(lightColor, In.WorldPos, i);
    }
    
    color *= lightColor;
//    color = saturate(color);

    return color;
}
// CatPattern
float4 Select_catpattern(VSOut In) : SV_TARGET
{        
    float4 color = (float) 0.0f;
    float2 uv = In.UV;
    uv.y += Time.y / 5.0;
    color = albedoTexture.Sample(pointSampler, uv);
    
    float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.0f);
       
    for (int i = 0; i < lightsAttribute[0].pad; i++)
    {
 //       CalculateLight2D(lightColor, In.WorldPos, i);
    }
    
    color *= lightColor;
//    color = saturate(color);

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
    
    float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.0f);
       
    for (int i = 0; i < lightsAttribute[0].pad; i++)
    {
//        CalculateLight2D(lightColor, In.WorldPos, i);
    }
    
    color *= lightColor;
//    color = saturate(color);

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
    
    float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.0f);
       
    for (int i = 0; i < lightsAttribute[0].pad; i++)
    {
//        CalculateLight2D(lightColor, In.WorldPos, i);
    }

    color *= lightColor;
//    color = saturate(color);

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
    
    float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.0f);
    
    for (int i = 0; i < lightsAttribute[0].pad; i++)
    {
//        CalculateLight2D(lightColor, In.WorldPos, i);
    }
    color *= lightColor;
//    color = saturate(color);

    return color;
}

float4 HPBar(VSOut In) : SV_TARGET
{
//    float4 color = (0.0f, 0.0f, 0.0f, 1.0f);
//    float2 UV = In.UV * (curHP / maxHP);  
//    color = albedoTexture.Sample(pointSampler, UV);  
//    return color;
    
    
    float4 color = (0.0f, 0.0f, 0.0f, 1.0f);
    
    // 여기서 비율을 계산합니다.
    float ratio = curHP / maxHP;
    
    // UV의 x 좌표가 ratio보다 크면 픽셀을 렌더링하지 않습니다.
    if (In.UV.x > ratio)
    {
        discard;
    }

//    color = albedoTexture.Sample(pointSampler, In.UV);
//    color = saturate(color);

    return color;
}   