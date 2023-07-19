#include "Gobj_Player.h"

#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgMeshRenderer.h"
#include "..\Engine_SOURCE\sgCollider2D.h"
#include "..\Engine_SOURCE\sgResources.h"

#include "SCRIPT_CameraScript.h"
#include "Char_Cheese.h"




namespace sg
{
	//Gobj_Character* Gobj_Player::mChar = nullptr;
	//std::vector<Gobj_Character*> Gobj_Player::mCompanies = {};

	Gobj_Player::Gobj_Player()
	{
		Gobj_Player::Initialize();
	}
	Gobj_Player::~Gobj_Player()
	{
	}
	void Gobj_Player::Initialize()
	{
		AddComp<SCRIPT_CameraScript>();
		mTr = GetComp<Transform>();
		mMr = AddComp<MeshRenderer>();
		mCol = AddComp<Collider2D>();
		mTr->SetPosition(0.0f, 0.0f, -1.0f);
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMr->SetMaterial(Resources::Find<Material>(L"Cheese_temp"));

		mMr->Initialize();

	}
	void Gobj_Player::Update()
	{
		//mMr = mChar->GetComp<MeshRenderer>();
		//if (mChar != nullptr)
		//{
		//	mChar->Update();
		//	mMr = mChar->GetComp<MeshRenderer>();
		//}

		GameObject::Update();
	}
	void Gobj_Player::LateUpdate()
	{
		//if (mChar != nullptr)
		//	mChar->LateUpdate();

		GameObject::LateUpdate();
	}
	void Gobj_Player::Render()
	{
		//if (mChar != nullptr)
		//{
		//	mMr = mChar->GetComp<MeshRenderer>();
		//	mChar->Render();
		//}

		GameObject::Render();
	}
	void Gobj_Player::OnCollisionEnter(Collider2D* other)
	{
		int a = 0;
	}
	void Gobj_Player::OnCollisionStay(Collider2D* other)
	{
	}
	void Gobj_Player::OnCollisionExit(Collider2D* other)
	{
	}
}