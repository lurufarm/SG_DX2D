#pragma once
#include "sgComputeShader.h"
#include "sgStructuredBuffer.h"

namespace sg::graphics
{
	class ParticleShader : public ComputeShader
	{
	public:
		ParticleShader();
		~ParticleShader();
		
		virtual void Binds() override;
		virtual void Clear() override;

		void SetParticleBuffer(StructuredBuffer* particleBuffer);
		void SetSharedBuffer(StructuredBuffer* sharedBuffer) { mSharedBuffer = sharedBuffer; }


	private:
		StructuredBuffer* mParticleBuffer;
		StructuredBuffer* mSharedBuffer;
	};
}
