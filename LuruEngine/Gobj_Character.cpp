#include "Gobj_Character.h"

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
		GameObject::Initialize();
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