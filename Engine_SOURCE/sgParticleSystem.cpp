#include "sgParticleSystem.h"
#include "sgTime.h"
#include "sgMesh.h"
#include "sgMaterial.h"
#include "sgResources.h"
#include "sgTransform.h"
#include "sgGameObject.h"
#include "sgConstantBuffer.h"
#include "sgRenderer.h"
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

namespace sg
{
	ParticleSystem::ParticleSystem()
		: mCount(0)
		, mStartPos(Vector4::Zero)
		, mEndPos(Vector4::Zero)
		, mStartSize(1.0f)
		, mEndSize(1.0f)
		, mStartAngle(0.0f)
		, mEndAngle(0.0f)
		, mSpeed(0.0f)
		, mStartColor(Vector4::Zero)
		, mEndColor(Vector4::Zero)
		, mMiddleColor(Vector4::Zero)
		, mLifeTime(0.0f)
		, mTime(0.0f)
		, mFrequency(0.0f)
		, mTarget(nullptr)
		, mPMaterial(nullptr)
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);	

		mPMaterial = Resources::Find<Material>(L"particletest");
		SetMaterial(mPMaterial);

		mCS = Resources::Find<ParticleShader>(L"ParticleSystemShader");

		for (size_t i = 0; i < mCount; i++)
		{
			Vector4 pos = Vector4::Zero;
			mParticles[i].position = pos;
			mParticles[i].direction = pos;
			mParticles[i].speed = 0.3f;
			mParticles[i].active = 0;
		}

		mSharedBuffer = new graphics::StructuredBuffer();
		mSharedBuffer->Create(sizeof(ParticleShared), 1, eViewType::UAV, nullptr, true);
	}
	ParticleSystem::~ParticleSystem()
	{
		delete mSharedBuffer;
		delete mBuffer;
	}
	void ParticleSystem::Initialize()
	{
		GameObject* owner = GetOwner();
		SetMaterial(mPMaterial);
		Vector3 pos = GetOwner()->GetComp<Transform>()->GetPosition();
		mStartPos = Vector4(pos.x, pos.y, 0.0f, 0.0f);
		mStartPos = RandomPos(mStartPos, mPosRange.x);

		for (size_t i = 0; i < 1000; i++)
		{
			mEndPos = Vector4(2.0f, 2.0f, 0.0f, 0.0f);
			mEndPos = RandomPos(mEndPos, mPosRange.y);

			if (mTarget)
			{
				Vector3 targetpos = mTarget->GetComp<Transform>()->GetPosition();
				mEndPos = Vector4(targetpos.x, targetpos.y, 0.0f, 1.0f);
				mEndPos = RandomPos(mEndPos, mPosRange.y);
			}

			mParticles[i].position = mStartPos;
			mParticles[i].direction = Vector4(mEndPos.x - mStartPos.x, mEndPos.y - mStartPos.y, 0.0f, 1.0f);
			mParticles[i].direction.Normalize();
			mParticles[i].color = mStartColor;
			mParticles[i].scale = Vector2(RandomScale(), RandomScale());
			mParticles[i].rotation = Vector2(RandomAngle(), RandomAngle());
			mParticles[i].speed = RandomTime(mSpeed);
			mParticles[i].creationTime = RandomTime(0.5f);
			mParticles[i].lifeTime = RandomTime(mLifeTime);
			mParticles[i].curTime = 0.0f;
			mParticles[i].active = 0;
		}

		mElapsedTime = 0.0f;
		mBuffer = new graphics::StructuredBuffer();
		mBuffer->Create(sizeof(Particle), mCount, eViewType::UAV, &mParticles);


	}
	void ParticleSystem::Update()
	{
	}
	void ParticleSystem::LateUpdate()
	{
		float AliveTime = mFrequency;
		mTime += Time::DeltaTime();
		mElapsedTime += Time::DeltaTime();

		if (mTime > AliveTime)
		{
			float f = (mTime / AliveTime);
			UINT AliveCount = (UINT)f;
			mTime = f - floor(f);

			ParticleShared shareData = {};
			shareData.sharedActiveCount = mCount / 10;
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

		mCS->SetParticleBuffer(mBuffer);
		mCS->SetSharedBuffer(mSharedBuffer);
		mCS->OnExcute();

		mBuffer->BindSRV(eShaderStage::VS, 14);
		mBuffer->BindSRV(eShaderStage::GS, 14);
		mBuffer->BindSRV(eShaderStage::PS, 14);

		mPMaterial->Binds();
		this->GetMesh()->RenderInstanced(mCount);

		//mBuffer->Clear();
	}
	void ParticleSystem::BindConstantBuffer()
	{
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Particle];

		renderer::ParticleCB data = {};
		Vector3 ownerpos = GetOwner()->GetComp<Transform>()->GetPosition();
		data.ownerPos = Vector4(ownerpos.x, ownerpos.y, ownerpos.z, 1.0f);
		data.elementCount = mCount;
		data.elpasedTime = mElapsedTime;
		data.deltaTime = Time::DeltaTime();
		data.startColor = mStartColor;
		data.middleColor = mMiddleColor;
		data.endColor = mEndColor;

		cb->SetData(&data);
		for (int i = 0; i < (int)eShaderStage::End; i++)
			cb->Bind((eShaderStage)i);
	}
	void ParticleSystem::InitializeRandomFunc()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
	}
	Vector4 ParticleSystem::RandomPos(Vector4 pos, float range)
	{
		InitializeRandomFunc();

		const float PI = 3.141592;
		float angle = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * 2 * PI);

		// random distance
		float randomRange = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * range);

		// angle + distance
		Vector4 randomPos = pos;
		randomPos.x += static_cast<float>(rand() / static_cast<float>(RAND_MAX) * range) * cos(angle);
		randomPos.y += static_cast<float>(rand() / static_cast<float>(RAND_MAX) * range) * sin(angle);
		//randomPos.z = -0.1f;

		return randomPos;
	}

	float ParticleSystem::RandomScale()
	{
		InitializeRandomFunc();

		std::uniform_real_distribution<> dis(mScaleRange.x, mScaleRange.y);
		float randomValue = dis(gen);

		return randomValue;
	}
	float ParticleSystem::RandomAngle()
	{
		InitializeRandomFunc();

		Vector4 direction = mEndPos - mStartPos;
		float angleInRadians = atan2(direction.y, direction.x);
		float angleInDegrees = angleInRadians * (180.0f / 3.141592);

		std::uniform_int_distribution<> dis(angleInDegrees - 30, angleInDegrees + 30);

		float randomAngle = dis(gen);

		randomAngle = sgGetAngleInRadian(randomAngle);

		return randomAngle;
	}
	float ParticleSystem::RandomTime(float time)
	{
		InitializeRandomFunc();

		std::uniform_real_distribution<> dis(0.0f, time * 2.0f);

		return dis(gen);
	}
	float ParticleSystem::RandomFloat(float value, float range)
	{
		return 0.0f;
	}
	void ParticleSystem::SetParticleOptions(UINT count, Vector2 pRange, Vector2 sRange, float speed, Vector4 sColor, Vector4 eColor, Vector4 mColor, float lTime, float freq)
	{
		mCount = count;
		mPosRange = pRange;
		mScaleRange = sRange;
		mSpeed = speed;
		mStartColor = sColor;
		mEndColor = eColor;
		mMiddleColor = mColor;
		mLifeTime = lTime;
		mFrequency = freq;
		mElapsedTime = 0.0f;
	}
}