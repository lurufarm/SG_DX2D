#include "sgParticleShader.h"
#include "sgRenderer.h"
#include "sgConstantBuffer.h"
#include "sgTime.h"

namespace sg::graphics
{
	ParticleShader::ParticleShader()
		: ComputeShader(128, 1, 1)
		, mParticleBuffer(nullptr)
	{
	}
	ParticleShader::~ParticleShader()
	{
	}
	void ParticleShader::Binds()
	{
		mParticleBuffer->BindUAV(0);
		mSharedBuffer->BindUAV(1);

		mGroupX = mParticleBuffer->GetStride() / mThreadGroupCountX + 1;
		mGroupY = 1;
		mGroupZ = 1;
	}
	void ParticleShader::Clear()
	{
		mParticleBuffer->Clear();
		mSharedBuffer->Clear();
	}
	void ParticleShader::SetParticleBuffer(StructuredBuffer* particleBuffer)
	{
		mParticleBuffer = particleBuffer;
	}
}