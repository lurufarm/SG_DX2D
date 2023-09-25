#include "globals.hlsli"
RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);

void UpdateParticle(int id)
{
    float t = elapsedTime;
    float t2 = (ParticleBuffer[id].lifeTime + ParticleBuffer[id].creationTime) / 2.0f;
    float totalLifeTime = ParticleBuffer[id].lifeTime + ParticleBuffer[id].creationTime;
    if (t < t2)
    {
        ParticleBuffer[id].curColor =
            lerp(ParticleBuffer[id].startColor
            , ParticleBuffer[id].middleColor, t / t2);
    }
    else
    {
        ParticleBuffer[id].curColor =
                lerp(ParticleBuffer[id].middleColor
            , ParticleBuffer[id].endColor
            , (t - t2) / (ParticleBuffer[id].lifeTime - t2));

    }
        
    float2 dir = normalize(ParticleBuffer[id].endPos - ParticleBuffer[id].startPos);
    ParticleBuffer[id].curPos += dir * ParticleBuffer[id].speed * deltaTime;
        
    float lerpTime = min(t / totalLifeTime, 1.0f);
        
    ParticleBuffer[id].curScale =
            lerp(ParticleBuffer[id].startScale, ParticleBuffer[id].endScale, lerpTime);
    ParticleBuffer[id].curAngle =
            lerp(ParticleBuffer[id].startAngle, ParticleBuffer[id].endAngle, lerpTime);
        
}


[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint id = DTid.x;
    
    if (particleCount <= id)
        return;
    
    
    if (ParticleBuffer[DTid.x].active == 0)
    {
        while (0 < ParticleSharedBuffer[0].ActiveSharedCount)
        {
            int origin = ParticleSharedBuffer[0].ActiveSharedCount;
            int exchange = origin - 1;
            
            // 쓰레드 동기화 Interlock 관련 함수
            
            InterlockedCompareExchange(ParticleSharedBuffer[0].ActiveSharedCount
                , origin, exchange, exchange);
                          
            if (origin == exchange)
            {
                ParticleBuffer[id].active = 1;
                break;
            }
        }
    }
    else
    {
        UpdateParticle(id);
    }
}