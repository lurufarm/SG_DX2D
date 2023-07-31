#include "Gobj_Bullet.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "Gobj_Player.h"
#include "SCRIPT_Bullet.h"
#include "SCRIPT_Player.h"
#include "SCRIPT_Company.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	class SCRIPT_Player;

	Gobj_Bullet::Gobj_Bullet()
	{
		mType = eBulletType::Cheese;
		AddComp<MeshRenderer>();
		AddComp<Collider2D>();
		mBulletOwner = nullptr;
	}
	Gobj_Bullet::~Gobj_Bullet()
	{
	}
	void Gobj_Bullet::initialize()
	{
		if (Player->GetTarget()->GetState() == Active)
		{
			if (mBulletOwner->GetIsPlayer())
			{
				mFirstPos = Player->GetComp<Transform>()->GetPosition();
				mTargetPos = Player->GetTarget()->GetComp<Transform>()->GetPosition();
			}
			else
			{
				mFirstPos = mBulletOwner->GetComp<Transform>()->GetPosition();
				mTargetPos = mBulletOwner->GetTarget()->GetComp<Transform>()->GetPosition();
			}
		}
	}
	void Gobj_Bullet::Update()
	{
		GameObject::Update();
	}
	void Gobj_Bullet::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Gobj_Bullet::Render()
	{
		GameObject::Render();
	}
}