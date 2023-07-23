#include "Gobj_Bullet.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "Gobj_Player.h"
#include "SCRIPT_Bullet.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Gobj_Bullet::Gobj_Bullet()
	{
		mType = eBulletType::Basic;
		AddComp<MeshRenderer>();
		AddComp<Collider2D>();
		mOwner = Player;
		//AddComp<SCRIPT_Bullet>();
	}
	Gobj_Bullet::~Gobj_Bullet()
	{
	}
	void Gobj_Bullet::initialize()
	{
		mFirstPos = Player->GetComp<Transform>()->GetPosition();
		mTargetPos = Player->GetTarget()->GetComp<Transform>()->GetPosition();
		GameObject::Initialize();
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