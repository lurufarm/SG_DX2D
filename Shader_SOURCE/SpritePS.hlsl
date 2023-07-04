
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

Texture2D albedoTexture : register(t0);

SamplerState pointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);

cbuffer Time : register(b1)
{
    float4 mTime;
}

float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float) 0.0f;
    color = albedoTexture.Sample(pointSampler, In.UV);
	
    return color;
}
// CatPattern
float4 Select_catpattern(VSOut In) : SV_TARGET
{        
    float4 color = (float) 0.0f;
    float2 uv = In.UV;
    uv.y += mTime.y / 5.0;
    color = albedoTexture.Sample(pointSampler, uv);
    
    return color;
}

// Lobby_Space1
float4 lobby_space1(VSOut In) : SV_TARGET
{
    float4 color = (float) 0.0f;
    float2 uv = In.UV;
    uv.x += mTime.y / 8.0; 
    uv.y += -mTime.y / 8.0;
    color = albedoTexture.Sample(pointSampler, uv);
    
    return color;
}

// Lobby_Space2
float4 lobby_space2(VSOut In) : SV_TARGET
{
    float4 color = (float) 0.0f;
    float2 uv = In.UV;
    uv.x += mTime.y / 10.0;
    uv.y += -mTime.y / 10.0;
    color = albedoTexture.Sample(pointSampler, uv);
    
    return color;
}