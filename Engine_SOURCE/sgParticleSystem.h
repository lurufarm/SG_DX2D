#pragma once
#include "sgMeshRenderer.h"
#include "sgStructuredBuffer.h"
#include "sgParticleShader.h"

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


		void InitializeParticles(int count, Vector2 spos, Vector2 dpos, Vector4 scolor, Vector4 mcolor, Vector4 dcolor, float sp, float ltime, float ctime = 0.0f);

		void SetCount(UINT cnt) { mCount = cnt; }
		void SetStartPos(Vector2 pos) { mDefaultParticle.startPos = pos; }
		void SetEndPos(Vector2 pos) { mDefaultParticle.endPos = pos; }
		void SetTexture(std::shared_ptr<Texture> tex)
		{
			mParticleTexture = tex;
			GetMaterial()->SetTexture(tex);
		}
		void SetPosRange(float range, float range2)
		{
			mStartPosRange = range;
			mEndPosRange = range2;
		}
		void SetScaleRange(float range, float range2)
		{
			mScaleRange1 = range;
			mScaleRange2 = range2;
		}

		void SetParticleColor(Vector4 startColor, Vector4 endColor, Vector4 middleColor = Vector4::Zero)
		{
			mDefaultParticle.startColor = startColor;
			mDefaultParticle.endColor = endColor;
			if (middleColor == Vector4::Zero)
			{
				mDefaultParticle.middleColor =
					Vector4::Lerp(
						mDefaultParticle.startColor
						, mDefaultParticle.endColor
						, 0.5);
			}
			else
				mDefaultParticle.middleColor = middleColor;
		}

		void SetLifeTime(float settime) { mDefaultParticle.lifeTime = settime; }
		void SetParticleSpeed(float speed) { mDefaultSpeed = speed; }

		void BindConstantBuffer();

		Vector2 RandomStartPos(Vector2 pos);
		Vector2 RandomEndPos(Vector2 pos);
		Vector2 RandomScale();
		float RandomAngle();
		float RandomTime(float time);
		float RandomFloat(float value, float range);
		UINT RandomUINT(UINT num, UINT range);


	private:
		graphics::StructuredBuffer* mParticleBuffer;
		graphics::StructuredBuffer* mSharedBuffer;

		std::shared_ptr<ParticleShader> mParticleShader;
		std::shared_ptr<Texture> mParticleTexture;

		Particle mParticles[1000];
		Particle mDefaultParticle;
		UINT mCount;
		float mTime;
		float mElapsedTime;
		float mStartPosRange;
		float mEndPosRange;
		float mScaleRange1;
		float mScaleRange2;
		float mDefaultSpeed;
	};
}