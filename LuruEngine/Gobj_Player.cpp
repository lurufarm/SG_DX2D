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
	Gobj_Character::CharStat Gobj_Player::mpStat = {};
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
		mMr = AddComp<MeshRenderer>();
		mMr->SetMesh(mpChar->GetComp<MeshRenderer>()->GetMesh());
		mMr->SetMaterial(mpChar->GetComp<MeshRenderer>()->GetMaterial());
		mMr->Initialize();
		mpStat = mpChar->GetStat();
		mCol = AddComp<Collider2D>();
	}
	void Gobj_Player::Update()
	{
		GameObject::Update();
	}
	void Gobj_Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Gobj_Player::Render()
	{
		GameObject::Render();
	}
}