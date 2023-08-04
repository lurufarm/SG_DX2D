#include "Gobj_Player.h"

#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgMeshRenderer.h"
#include "..\Engine_SOURCE\sgCollider2D.h"
#include "..\Engine_SOURCE\sgResources.h"

#include "SCRIPT_CameraScript.h"
#include "SCRIPT_Player.h"
#include "Char_Cheese.h"
#include "SCENE_PlayScene.h"


namespace sg
{
	Gobj_Character* Gobj_Player::mpChar = nullptr;

	Transform* Gobj_Player::mTr = nullptr;
	MeshRenderer* Gobj_Player::mMr = nullptr;
	Collider2D* Gobj_Player::mCol = nullptr;
	Animator* Gobj_Player::mAni = nullptr;
	Light* Gobj_Player::mLg = nullptr;

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


		SetMesh();
		mMr->SetMaterial(Resources::Find<Material>(L"AnimationMaterial"));
		mCol->SetCenter(Vector2(0.0f, -2.0f));
		mCol->SetSize(Vector2(0.4f, 0.7f));

		mLg = AddComp<Light>();
		mLg->SetType(eLightType::Point);
		mLg->SetRadius(50.0f);
		mLg->SetColor(Vector4(0.6f, 0.5f, 0.3f, 0.0f));

		mpChar = Gobj_Character::GetChar(L"Cheese");
		SetChar(Gobj_Character::GetChar(L"Cheese"));
		mMr->Initialize();


		AddComp<SCRIPT_Player>();


	}
	void Gobj_Player::Update()
	{
		if (PlayScene::GetTime())
		{
			mLg->SetColor(Vector4(0.0f));
		}
		else
		{
			mLg->SetColor(Vector4(0.6f, 0.5f, 0.3f, 0.5f));
		}
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