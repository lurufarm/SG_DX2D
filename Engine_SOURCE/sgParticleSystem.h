#pragma once
#include "sgMeshRenderer.h"
#include "sgStructuredBuffer.h"

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

	private:
		graphics::StructuredBuffer* mBuffer;

		UINT	mCount;
		Vector4	mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float mLifeTime;
	};
}
