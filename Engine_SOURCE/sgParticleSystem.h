#pragma once
#include "sgMeshRenderer.h"
#include "sgStructuredBuffer.h"
#include "sgParticleShader.h"
#include "..\Engine_SOURCE\sgMaterial.h"
#include "..\Engine_SOURCE\sgResources.h"

namespace sg
{
	class ParticleSystem : public MeshRenderer
	{
	public:
		ParticleSystem();
		~ParticleSystem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		void BindConstantBuffer();

		void InitializeRandomFunc();
		Vector4 RandomPos(Vector4 pos, float range);
		float RandomScale();
		float RandomAngle();
		float RandomTime(float time);
		float RandomFloat(float value, float range);

		void SetParticleMaterial(std::wstring material) { mPMaterial = Resources::Find<sg::graphics::Material>(material); }
		void SetParticleOptions(UINT count, Vector2 sRange, float speed, Vector4 sColor, Vector4 eColor, Vector4 mColor, float lTime, float freq);
		void SetTarget(GameObject* target) { mTarget = target; }
		Vector4 GetStartColor() { return mStartColor; }
		Vector4 GetMiddleColor() { return mMiddleColor; }
		Vector4 GetEndColor() { return mEndColor; }


	private:
		graphics::StructuredBuffer* mBuffer;
		graphics::StructuredBuffer* mSharedBuffer;
		std::shared_ptr<Material> mPMaterial;
		std::shared_ptr<ParticleShader> mCS;

		Particle mParticles[1000];

		UINT  mCount;
		Vector4 mStartPos;
		Vector4 mEndPos;
		float mStartSize;
		float mEndSize;
		Vector2 mScaleRange;
		float mStartAngle;
		float mEndAngle;
		float mSpeed;
		Vector4 mStartColor;
		Vector4 mEndColor;
		Vector4 mMiddleColor;

		float   mLifeTime;
		float	mFrequency;

		GameObject* mTarget;

		float mTime;
		float mElapsedTime;


	};
}
