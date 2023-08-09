#include "Gobj_MobProjectile.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "Gobj_Player.h"
#include "SCRIPT_Bullet.h"
#include "SCRIPT_Player.h"
#include "SCRIPT_Company.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	class SCRIPT_Player;
	class SCRIPT_RangedMob;

	//Gobj_MobProjectile::Gobj_MobProjectile()
	//{
	//	mType = eMProjType::PoisonOrb;
	//	AddComp<MeshRenderer>();
	//	AddComp<Collider2D>();
	//}

	Gobj_MobProjectile::Gobj_MobProjectile()
	{
		mType = eMProjType::PoisonOrb;
		AddComp<MeshRenderer>();
		AddComp<Collider2D>();
		//mFirstPos = BulletOwner->GetComp<Transform>()->GetPosition();
		//mTargetPos = Player->GetComp<Transform>()->GetPosition();
	}
	Gobj_MobProjectile::~Gobj_MobProjectile()
	{
	}
	void Gobj_MobProjectile::Initialize()
	{
	}
	void Gobj_MobProjectile::Update()
	{
		GameObject::Update();
	}
	void Gobj_MobProjectile::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Gobj_MobProjectile::Render()
	{
		GameObject::Render();
	}
}