#include "Bullet_SKGroundFires.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Bullet_SKGroundFire.h"
#include <random>

namespace sg
{
	sg::Bullet_SKGroundFires::Bullet_SKGroundFires(Gobj_Monster* BulletOwner)
	{
		SetName(L"SKGroundFires");
		mProjOwner = BulletOwner;
		Bullet_SKGroundFires::Initialize();
	}
	Bullet_SKGroundFires::~Bullet_SKGroundFires()
	{
	}
	void Bullet_SKGroundFires::Initialize()
	{
		RandAngle();
		mAngle *= (3.141592 / 180.0f);

		for (size_t i = 0; i < 4; i++)
		{
			float a = i * 90;
			float added_angle = a * (3.141592 / 180.0f);
			float x = cos(mAngle + added_angle);
			float y = sin(mAngle + added_angle);

			mBullets[i] = object::SKGroundFire(Vector2(x, y), mProjOwner);
		}
	}
	void Bullet_SKGroundFires::Update()
	{
		if (mBullets[3] == nullptr || mBullets[3]->GetState() != eState::Active)
		{
			SetState(eState::Dead);
		}
		GameObject::Update();
	}
	void Bullet_SKGroundFires::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Bullet_SKGroundFires::Render()
	{
		GameObject::Render();
	}
	void Bullet_SKGroundFires::RandAngle()
	{
		std::random_device rd;  // 랜덤 시드를 얻기 위한 장치
		std::mt19937 gen(rd());  // 메르센 트위스터 난수 생성기 초기화
		std::uniform_int_distribution<> dist(0, 30);  // 0과 1 사이의 균등 분포

		mAngle = dist(gen);
	}
}