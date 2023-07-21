#include "Gobj_Character.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Gobj_Character::Gobj_Character()
	{
		AddComp<MeshRenderer>();
	}
	Gobj_Character::~Gobj_Character()
	{
	}
	void Gobj_Character::Initialize()
	{
		mTr = Player->GetComp<Transform>();
		mCol = Player->GetComp<Collider2D>();
		GameObject::Initialize();
	}
	void Gobj_Character::Update()
	{
		mTr = Player->GetComp<Transform>();
		mCol = Player->GetComp<Collider2D>();

		if (mStat.mExp >= 100.0f)
		{
			mStat.mLev++;
		}
		GameObject::Update();
	}
	void Gobj_Character::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Gobj_Character::Render()
	{
		GameObject::Render();
	}
}