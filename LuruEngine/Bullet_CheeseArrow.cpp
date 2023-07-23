#include "Bullet_CheeseArrow.h"
#include "Gobj_Player.h"
#include "SCRIPT_Bullet.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Bullet_CheeseArrow::Bullet_CheeseArrow()
	{
		SetName(L"CheeseArrow");
		Bullet_CheeseArrow::Initialize();
	}
	Bullet_CheeseArrow::~Bullet_CheeseArrow()
	{
	}
	void Bullet_CheeseArrow::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mType = eBulletType::Basic;
		SetMesh();
		SetMaterial(L"Arrow");
		mMr->Initialize();
		mFirstPos = Player->GetComp<Transform>()->GetPosition();
		mTargetPos = Player->GetTarget()->GetComp<Transform>()->GetPosition();

		Vector3 direction = mTargetPos - mFirstPos;
		direction.Normalize();
		float angleRad = std::acos(direction.x); // acos() 함수를 사용하여 x축과의 각도를 구합니다.
		if (direction.y < 0) // 방향 벡터의 y값이 음수면 각도를 음수로 변환합니다.
		{
			angleRad = -angleRad;
		}
		float angleDegree = (angleRad * 180.0f / 3.1415926535f) - 90.0f;
		mTr = GetComp<Transform>();
		mTr->SetRotation(Vector3(0.0f, 0.0f, angleDegree));
		AddComp<SCRIPT_Bullet>();
	}
	void Bullet_CheeseArrow::Update()
	{
		Gobj_Bullet::Update();
	}
	void Bullet_CheeseArrow::LateUpdate()
	{
		Gobj_Bullet::LateUpdate();
	}
	void Bullet_CheeseArrow::Render()
	{
		Gobj_Bullet::Render();
	}
}