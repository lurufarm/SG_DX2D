#include "globals.hlsli"
RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);

[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (elementCount <= DTid.x)
        return;
    
    float totalLifeTime = ParticleBuffer[DTid.x].lifeTime + ParticleBuffer[DTid.x].creationTime;
    float t = ParticleBuffer[DTid.x].curTime / totalLifeTime;

    if (ParticleBuffer[DTid.x].active == 0 && t <= 1.0f)
    {
        //if there are active particles to process
        while (ParticleSharedBuffer[0].ActiveSharedCount > 0)
        {
            int origin = ParticleSharedBuffer[0].ActiveSharedCount;
            int exchange = origin - 1; // <- process one particle at one time
            
            // ������ ����ȭ Interlock ���� �Լ�            
            InterlockedCompareExchange(ParticleSharedBuffer[0].ActiveSharedCount
                , origin, exchange, exchange); //activeSharedCount�� origin���� exchange�� �ٲٱ� �õ�.
            
//            if (origin == exchange) // activeSharedCount update�� �����ߴٸ� particle initialize
//            {
            if (ParticleBuffer[DTid.x].creationTime <= elapsedTime)
            {
                ParticleBuffer[DTid.x].active = 1;
                ParticleBuffer[DTid.x].curTime = ParticleBuffer[DTid.x].creationTime;
                ParticleBuffer[DTid.x].position = ownerPos;
            }
            break;
//            }
        }
    }
    else
    {
        // Update   

        if (t > 1.0f)
            ParticleBuffer[DTid.x].active = 0;
        else
        {
            ParticleBuffer[DTid.x].curTime += deltaTime;
            ParticleBuffer[DTid.x].position.x += ParticleBuffer[DTid.x].direction.x * ParticleBuffer[DTid.x].speed * deltaTime;
            ParticleBuffer[DTid.x].position.y += ParticleBuffer[DTid.x].direction.y * ParticleBuffer[DTid.x].speed * deltaTime;
            ParticleBuffer[DTid.x].position.z = ownerPos.z;
            ParticleBuffer[DTid.x].position.w = 1.0f;
            

            float halfTime = totalLifeTime / 2.0f;
            if (ParticleBuffer[DTid.x].curTime <= halfTime)
            {
                float ratio = ParticleBuffer[DTid.x].curTime / halfTime; // 0���� 1�� ��ȭ�մϴ�.
                ParticleBuffer[DTid.x].color = lerp(startColor, middleColor, ratio);
            }
            else if (ParticleBuffer[DTid.x].curTime > halfTime)
            {
                float ratio = (ParticleBuffer[DTid.x].curTime - halfTime) / halfTime; // 0���� 1�� ��ȭ�մϴ�.
                ParticleBuffer[DTid.x].color = lerp(middleColor, endColor, ratio);
            }
        }
    }
}