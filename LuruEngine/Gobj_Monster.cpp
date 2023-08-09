#include "Gobj_Monster.h"
#include "..\Engine_SOURCE\sgAnimator.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;


namespace sg
{
	std::map<std::wstring, Gobj_Monster*> Gobj_Monster::mAllMobs = {};

	Gobj_Monster::Gobj_Monster()
	{
		AddComp<MeshRenderer>();
		AddComp<Collider2D>();
		AddComp<Animator>();
		mPlayer = (GameObject*)Player;
		mTargeted = false;
	}
	Gobj_Monster::~Gobj_Monster()
	{
	}
	void Gobj_Monster::Initialize()
	{
		AddMob(this->GetName(), this);
	}
	void Gobj_Monster::Update()
	{
		GameObject::Update();
	}
	void Gobj_Monster::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Gobj_Monster::Render()
	{
		GameObject::Render();
	}
}