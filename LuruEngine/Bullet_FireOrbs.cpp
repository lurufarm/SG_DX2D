#include "Bullet_FireOrbs.h"
#include "Bullet_FireOrb.h"
#include "sgObject.h"
#include <random>

namespace sg
{
	Bullet_FireOrbs::Bullet_FireOrbs(Gobj_Monster* BulletOwner)
	{
		SetName(L"FireOrbs");
		mProjOwner = BulletOwner;
		Bullet_FireOrbs::Initialize();
	}
	Bullet_FireOrbs::~Bullet_FireOrbs()
	{
	}
	void Bullet_FireOrbs::Initialize()
	{
		RandAngle();
		mAngle *= (3.141592 / 180.0f);

		for (size_t i = 0; i < 15; i++)
		{
			float a = i * 24;
			float added_angle = a * (3.141592 / 180.0f);
			float x = cos(mAngle + added_angle);
			float y = sin(mAngle + added_angle);

			mBullets[i] = object::FireOrb(Vector2(x, y), mProjOwner);
		}
	}
	void Bullet_FireOrbs::Update()
	{
		if (mBullets[14] == nullptr || mBullets[14]->GetState() != eState::Active)
		{
			SetState(eState::Dead);
		}
		GameObject::Update();
	}
	void Bullet_FireOrbs::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Bullet_FireOrbs::Render()
	{
		GameObject::Render();
	}
	void Bullet_FireOrbs::RandAngle()
	{
		std::random_device rd;  // 랜덤 시드를 얻기 위한 장치
		std::mt19937 gen(rd());  // 메르센 트위스터 난수 생성기 초기화
		std::uniform_int_distribution<> dist(0, 30);  // 0과 1 사이의 균등 분포

		mAngle = dist(gen);
	}
}