#include "Gobj_Character.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	std::map<std::wstring, Gobj_Character*> Gobj_Character::mAllChars = {};

	Gobj_Character::Gobj_Character()
	{
		AddComp<MeshRenderer>();
		AddComp<Animator>();
		mIsPlayer = false;
		//mTransParent = false;
	}
	Gobj_Character::~Gobj_Character()
	{
	}
	void Gobj_Character::Initialize()
	{
		AddChar(this->GetName(), this);
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