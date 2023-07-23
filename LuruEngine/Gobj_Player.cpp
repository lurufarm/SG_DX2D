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

		SetMesh();
		mMr->SetMaterial(Resources::Find<Material>(L"Animationmaterial"));
		//mMr->SetMaterial(mpChar->GetComp<MeshRenderer>()->GetMaterial());
		//mMr->Initialize();
		//mMr->Initialize();
		mTr->SetScale(Vector3(100.0f, 100.0f, 1.0f));

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"test", L"..\\Resources\\Character\\Cheese\\cheese.png");
		mAni->Create(L"Ani_Cheese_Idle", atlas, Vector2(0.0f, 20.0f), Vector2(24.0f, 20.0f), 9, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Cheese_Move", atlas, Vector2(0.0f, 0.0f), Vector2(24.0f, 20.0f), 8, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Cheese_Attack", atlas, Vector2(0.0f, 40.0f), Vector2(24.0f, 20.0f), 4, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Cheese_Death", atlas, Vector2(0.0f, 60.0f), Vector2(24.0f, 20.0f), 18, Vector2::Zero, 0.05f);

		//mAni->PlayAnimation(L"Ani_Cheese_Idle", true, 1);
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
		//if (mMr->GetMaterial() != nullptr)
		GameObject::Render();
	}
}