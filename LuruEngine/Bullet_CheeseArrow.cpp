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