#include "Gobj_Character.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Gobj_Character::Gobj_Character()
	{
		AddComp<MeshRenderer>();
		AddComp<Animator>();
	}
	Gobj_Character::~Gobj_Character()
	{
	}
	void Gobj_Character::Initialize()
	{
	}
	void Gobj_Character::Update()
	{
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