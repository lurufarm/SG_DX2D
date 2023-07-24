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

	Transform* Gobj_Player::mTr = nullptr;
	MeshRenderer* Gobj_Player::mMr = nullptr;
	Collider2D* Gobj_Player::mCol = nullptr;
	Animator* Gobj_Player::mAni = nullptr;

	Gobj_Character::CharStat Gobj_Player::mpStat = {};
	std::vector<Gobj_Character*> Gobj_Player::mCompanies = {};

	bool Gobj_Player::mEnemyNearby = false;

	Gobj_Player::Gobj_Player()
	{
		SetName(L"ME");
	}
	Gobj_Player::~Gobj_Player()
	{
	}
	void Gobj_Player::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = AddComp<MeshRenderer>();
		mCol = AddComp<Collider2D>();
		mAni = AddComp<Animator>();

		//mTr->SetScale(24.0f, 20.0f, 1.0f);
		SetMesh();
		mMr->SetMaterial(Resources::Find<Material>(L"Animationmaterial"));
		mCol->SetCenter(Vector2(0.0f, -2.0f));
		mCol->SetSize(Vector2(0.4f, 0.7f));


		AddComp<SCRIPT_Player>();
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