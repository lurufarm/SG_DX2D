
cbuffer Transform : register(b0)
{
    row_major matrix WorldMatrix;
    row_major matrix ViewMatrix;
    row_major matrix ProjectionMatrix;
}


cbuffer Grid : register(b2)
{
    float4 CameraPosition;
    float2 CameraScale;
    float2 Resolution;
}

cbuffer Animator : register(b3)
{
    float2 SpriteLeftTop; 
    float2 SpriteSize; 
    float2 SpriteOffset;
    float2 AtlasSize;
    uint animationType;
    float3 dummy;
}

cbuffer MyCB : register(b4)
{
    int CollidingColor;
    int TileIndex;
    int none1;
    int none2;
}

cbuffer Time : register(b5)
{
    float4 Time;
}

cbuffer TransParent : register(b6)
{
    int alphaValue;
    float3 pad;
}

cbuffer HPBar : register(b7)
{
    float maxHP;
    float curHP;
    float2 padHP;
}

cbuffer ParticleSystem : register(b8)
{
    float4 ownerPos;
    float4 startColor;
    float4 middleColor;
    float4 endColor;
    
    uint elementCount;
    float elapsedTime;
    float deltaTime;
    int padd2;
}

cbuffer Noise : register(b9)
{
    float4 noiseTextureSize;
}

Texture2D albedoTexture : register(t0);
Texture2D atlasTexture : register(t12);
Texture2D noiseTexture : register(t15);

struct LightAttribute
{
    float4 color;
    float4 position;
    float4 direction;
    
    uint type;
    float radius;
    float angle;
    int pad;
};

struct Particle
{
    float4 position;
    float4 direction;
    float4 color;
    float2 scale;
    float2 rotation;

    float speed;
    float lifeTime;
    float creationTime;
    float curTime;

    uint active;
    float particlePad[3];
};

struct ParticleShared
{
    uint ActiveSharedCount;
};

StructuredBuffer<LightAttribute> lightsAttribute : register(t13);
StructuredBuffer<Particle> particles : register(t14);

SamplerState pointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);

static float GaussianFilter[5][5] =
{
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.0219f, 0.0983f, 0.1621f, 0.0983f, 0.0219f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
};

float4 GaussianBlur(float2 UV)
{
    float4 Out = (float4) 0.0f;
    
    if (1.f < UV.x)
        UV.x = frac(UV.x);
    else if (UV.x < 0.0f)
        UV.x = 1.0f + frac(UV.x);
    
    if (1.f < UV.y)
        UV.y = frac(UV.y);
    else if (UV.y < 0.0f)
        UV.y = 1.0f + frac(UV.y);
    
    int2 iUV = UV * noiseTextureSize.xy;
    iUV -= int2(2, 2);
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int2 idx = int2(iUV.y + i, iUV.x + j);
            Out += noiseTexture[idx] * GaussianFilter[i][j];
        }
    }
    
    return Out;
}

void CalculateLight2D(in out float4 lightColor, float3 position, int idx)
{        
    if (0 == lightsAttribute[idx].type)
    {
        lightColor += lightsAttribute[idx].color;
    }
    else if (1 == lightsAttribute[idx].type)
    {
        float length = distance(position.xy, lightsAttribute[idx].position.xy);
        
        if (length < lightsAttribute[idx].radius)
        {
//            float ratio = 1.0f - (length / lightsAttribute[idx].radius);
            float ratio = 1.0f - smoothstep(0, lightsAttribute[idx].radius, length);
            lightColor += lightsAttribute[idx].color * ratio;
        }
    }
}
float4x4 CreateTranslationMatrix(float x, float y, float z)
{
    return float4x4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, 1,
        x, y, z, 1
    );
}
float4x4 CreateTranslationMatrix(float3 translation)
{
    return CreateTranslationMatrix(translation.x, translation.y, translation.z);
}

float4x4 CreateScaleMatrix(float x, float y, float z)
{
    return float4x4(
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    );
}

float4x4 CreateScaleMatrix(float3 scale)
{
    return CreateScaleMatrix(scale.x, scale.y, scale.z);
}

float4x4 CreateScaleMatrix(float scale, bool scaleZ = false)
{
    return CreateScaleMatrix(scale, scale, scaleZ ? scale : 1);
}
float4x4 CreateRotationMatrix(float angle, float3 axis)
{
    float c, s;
    sincos(angle, s, c);

    float t = 1 - c;
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    return float4x4(
        t * x * x + c, t * x * y - s * z, t * x * z + s * y, 0,
        t * x * y + s * z, t * y * y + c, t * y * z - s * x, 0,
        t * x * z - s * y, t * y * z + s * x, t * z * z + c, 0,
        0, 0, 0, 1
    );
}