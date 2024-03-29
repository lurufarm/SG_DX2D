#include "Gobj_Bullet.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
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
		mThisNum = 1;
	}
	Gobj_Bullet::~Gobj_Bullet()
	{
	}
	void Gobj_Bullet::Initialize()
	{
		if (SceneManager::GetActiveScene()->GetLayer(eLayerType::Monster).GetGameObjects().size() > 0)
		{
			if (mBulletOwner->GetIsPlayer())
			{
				mFirstPos = Player->GetComp<Transform>()->GetPosition();
				mLastPos = Player->GetTarget()->GetComp<Transform>()->GetPosition();
				mTarget = Player->GetTarget();
			}
			else
			{
				mFirstPos = mBulletOwner->GetComp<Transform>()->GetPosition();
				mLastPos = mBulletOwner->GetComp<SCRIPT_Company>()->GetTarget()->GetComp<Transform>()->GetPosition();
				mTarget = mBulletOwner->GetComp<SCRIPT_Company>()->GetTarget();
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