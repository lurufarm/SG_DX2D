#include "sgParticleSystem.h"

#include "sgTime.h"
#include "sgConstantBuffer.h"
#include "sgStructuredBuffer.h"
#include "sgParticleShader.h"
#include "sgRenderer.h"
#include "sgMesh.h"
#include "sgMaterial.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgGameObject.h"
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

namespace sg
{
	ParticleSystem::ParticleSystem()
		: mCount(0)
		, mTime(0.0f)
		, mStartPosRange(0.3f)
		, mEndPosRange(0.3f)
		, mScaleRange1(0.8f)
		, mScaleRange2(1.2f)
		, mDefaultSpeed(5.0f)

	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);
		mParticleShader = Resources::Find<ParticleShader>(L"ParticleSystemShader");

		mDefaultParticle = {};
	}
	ParticleSystem::~ParticleSystem()
	{
		delete mSharedBuffer;
		delete mParticleBuffer;
	}
	void ParticleSystem::Initialize()
	{
		for (size_t i = 0; i < mCount; i++)
		{
			//Particle particle;

			mParticles[i].particleCount = mCount;
			mParticles[i].active = 1;
			mParticles[i].startColor = mDefaultParticle.startColor;
			mParticles[i].middleColor = mDefaultParticle.middleColor;
			mParticles[i].endColor = mDefaultParticle.endColor;
			mParticles[i].curColor = mDefaultParticle.startColor;
			mParticles[i].startPos = RandomStartPos(mDefaultParticle.startPos);
			mParticles[i].endPos = RandomEndPos(mDefaultParticle.endPos);
			mParticles[i].curPos = mParticles[i].startPos;
			mParticles[i].startScale = RandomScale();
			mParticles[i].endScale = RandomScale();
			mParticles[i].curScale = mParticles[i].startScale;
			mParticles[i].startAngle = RandomAngle();
			mParticles[i].endAngle = RandomAngle();
			mParticles[i].curAngle = mParticles[i].startAngle;
			mParticles[i].speed = RandomFloat(mDefaultParticle.speed, .0f);
			mParticles[i].lifeTime = RandomTime(mDefaultParticle.lifeTime);
			mParticles[i].creationTime = RandomTime(0.15);
			mParticles[i].particleInWorldSpace = true;

		}

		mTime = 0.0f;

		mParticleBuffer = new graphics::StructuredBuffer();
		mParticleBuffer->Create(sizeof(Particle), 1000, eViewType::UAV, &mParticles, true);

		mSharedBuffer = new graphics::StructuredBuffer();
		mSharedBuffer->Create(sizeof(ParticleShared), 1, eViewType::UAV, nullptr, true);
	}
	void ParticleSystem::Update()
	{
	}
	void ParticleSystem::LateUpdate()
	{
		float AliveTime = 0.05f;
		mTime += Time::DeltaTime();
		mElapsedTime = Time::DeltaTime();
		if (mTime > AliveTime)
		{
			float f = (mTime / AliveTime);
			UINT AliveCount = (UINT)f;
			mTime = f - floor(f);

			ParticleShared shareData = {};
			shareData.sharedActiveCount = 4;
			mSharedBuffer->SetData(&shareData, 1);
		}
		else
		{
			ParticleShared shareData = {};
			shareData.sharedActiveCount = 0;
			mSharedBuffer->SetData(&shareData, 1);
		}

	}
	void ParticleSystem::Render()
	{
		GetOwner()->GetComp<Transform>()->BindConstantBuffer();
		BindConstantBuffer();

		mParticleShader->SetParticleBuffer(mParticleBuffer);
		mParticleShader->SetSharedBuffer(mSharedBuffer);
		mParticleShader->OnExcute();

		
		mParticleBuffer->BindSRV(eShaderStage::VS, 14);
		mParticleBuffer->BindSRV(eShaderStage::GS, 14);
		mParticleBuffer->BindSRV(eShaderStage::PS, 14);

		GetMaterial()->SetTexture(mParticleTexture);
		GetMaterial()->Binds();
		GetMesh()->RenderInstanced(mCount);

		mParticleBuffer->Clear();
		GetMaterial()->Clear();
	}

	void ParticleSystem::InitializeParticles(int count, Vector2 spos, Vector2 dpos, Vector4 scolor, Vector4 mcolor, Vector4 dcolor, float sp, float ltime, float ctime)
	{
		mCount = count;
		mDefaultParticle.startPos = spos;
		mDefaultParticle.endPos = dpos;
		mDefaultParticle.startColor = scolor;
		mDefaultParticle.middleColor = mcolor;
		mDefaultParticle.endColor = dcolor;
		mDefaultParticle.lifeTime = ltime;
		mDefaultParticle.creationTime = ctime;
		mDefaultParticle.speed = sp;
	}

	void ParticleSystem::BindConstantBuffer()
	{
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Particle];
		renderer::ParticleCB data = {};

		data.elapsedTime = mElapsedTime;
		data.deltaTime = Time::DeltaTime();
		data.particleCount = mCount;

		cb->SetData(&data);

		for (int i = 0; i < (int)eShaderStage::End; i++)
			cb->Bind((eShaderStage)i);
	}

	Vector2 ParticleSystem::RandomStartPos(Vector2 pos)
	{
		const float PI = 3.141592;
		float angle = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * 2 * PI);

		// random distance
		float range = mStartPosRange;
		float randomRange = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * range);

		// angle + distance
		Vector2 randomPos = pos;
		randomPos.x += static_cast<float>(rand() / static_cast<float>(RAND_MAX) * range) * cos(angle);
		randomPos.y += static_cast<float>(rand() / static_cast<float>(RAND_MAX) * range) * sin(angle);
		//randomPos.z = -0.1f;

		return randomPos;
	}

	Vector2 ParticleSystem::RandomEndPos(Vector2 pos)
	{
		const float PI = 3.141592;
		float angle = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * 2 * PI);

		// random distance
		float range = mEndPosRange;
		float randomRange = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * range);

		// angle + distance
		Vector2 randomPos = pos;
		randomPos.x += static_cast<float>(rand() / static_cast<float>(RAND_MAX) * range) * cos(angle);
		randomPos.y += static_cast<float>(rand() / static_cast<float>(RAND_MAX) * range) * sin(angle);
		//randomPos.z = -0.1f;

		return randomPos;
	}

	Vector2 ParticleSystem::RandomScale()
	{
		std::uniform_real_distribution<> dis(mScaleRange1, mScaleRange2);
		float randomValue = dis(gen);

		return Vector2(randomValue, randomValue);
	}
	float ParticleSystem::RandomAngle()
	{

		Vector2 direction = mDefaultParticle.endPos - mDefaultParticle.startPos;
		float angleInRadians = atan2(direction.y, direction.x);
		float angleInDegrees = angleInRadians * (180.0f / 3.141592);

		std::uniform_int_distribution<> dis(angleInDegrees - 15, angleInDegrees + 15);

		float randomAngle = dis(gen);

		randomAngle *= 3.141592f / 180.0f;

		return randomAngle;
	}
	float ParticleSystem::RandomTime(float time)
	{
		std::uniform_real_distribution<> dis(-0.15, 0.15);

		return time += dis(gen);
	}
	float ParticleSystem::RandomFloat(float value, float range)
	{
		std::uniform_real_distribution<> dis(value - range, value + range);
		return dis(gen);
	}
	UINT ParticleSystem::RandomUINT(UINT num, UINT range)
	{
		return 0;
	}
}