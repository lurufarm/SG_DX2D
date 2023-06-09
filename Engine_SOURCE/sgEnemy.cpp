#include "sgEnemy.h"

#include "sgRenderer.h"
#include "sgGraphicDevice_Dx11.h"

#include "sgNemo.h"

#include "sgInput.h"
#include "sgTime.h"

#include <random>


namespace sg
{
	using namespace renderer;

	int Enemy::mEnemynum = 0;

	Enemy::Enemy()
		: mState(eState::Active)
		, mDeath(false)
		, mStat{}
	{
		mEnemynum++;

		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_real_distribution<float> randomscale(10.0f, 25.0f);
		float scale = randomscale(gen);
		float pos[2] = {};
		std::uniform_real_distribution<float> randomxpos(-800.0f, 800.0f);
		std::uniform_real_distribution<float>randomypos(-450.0f, 450.0f);
		pos[0] = randomxpos(gen);
		pos[1] = randomypos(gen);

		float color[3] = {};
		for (size_t i = 0; i < 3; i++)
		{
			std::uniform_real_distribution<float> randomcolor(0.0f, 1.0f);
			color[i] = randomcolor(gen);
		}
		SetStat(scale, Vector3(pos[0], pos[1], 0.0f), Vector4(color[0], color[1], color[2], 1.0f));
	}
	Enemy::~Enemy()
	{
	}
	void Enemy::Initialize()
	{
		GameObject::Initialize();
	}
	void Enemy::Update()
	{
		GameObject::Update();
	}
	void Enemy::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Enemy::Render()
	{
		renderer::constantBuffer->SetData(&mStat);
		renderer::constantBuffer->Bind(eShaderStage::VS);

		renderer::mesh->BindBuffer();
		renderer::shader->Binds();
		graphics::GetDevice()->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);

		GameObject::Render();
	}
}