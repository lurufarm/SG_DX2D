#include "Gobj_Player.h"

#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgMeshRenderer.h"
#include "..\Engine_SOURCE\sgCollider2D.h"
#include "..\Engine_SOURCE\sgResources.h"

#include "SCRIPT_CameraScript.h"
#include "SCRIPT_Player.h"
#include "Char_Cheese.h"


namespace sg
{
	Gobj_Character* Gobj_Player::mpChar = nullptr;
	//Gobj_Character::BasicStat Gobj_Player::mpStat = {};
	std::vector<Gobj_Character*> Gobj_Player::mCompanies = {};
	bool Gobj_Player::mEnemyNearby = false;

	Gobj_Player::Gobj_Player()
		: mMr(nullptr)
		, mTr(nullptr)
		, mCol(nullptr)
	{
		SetName(L"ME");
		AddComp<SCRIPT_Player>();
	}
	Gobj_Player::~Gobj_Player()
	{
	}
	void Gobj_Player::Initialize()
	{
		mMr = mpChar->GetComp<MeshRenderer>();
	}
	void Gobj_Player::Update()
	{
		if (mpChar != nullptr)
		{
			mMr = mpChar->GetComp<MeshRenderer>();
			//mCol = mpChar->GetComp<Collider2D>();
			//mpStat = mpChar->GetStat();
		}
		GameObject::Update();
	}
	void Gobj_Player::LateUpdate()
	{
		mMr = mpChar->GetComp<MeshRenderer>();

		GameObject::LateUpdate();
	}
	void Gobj_Player::Render()
	{
		mMr = mpChar->GetComp<MeshRenderer>();

		GameObject::Render();
	}
}