#include "Gobj_Character.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Gobj_Character::Gobj_Character()
	{
		AddComp<MeshRenderer>();
		AddComp<Animator>();
		mIsPlayer = false;
	}
	Gobj_Character::~Gobj_Character()
	{
	}
	void Gobj_Character::Initialize()
	{
		SceneManager::AddChar(this->GetName(), this);
	}
	void Gobj_Character::Update()
	{
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