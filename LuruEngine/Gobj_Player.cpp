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

#include "UI_HpBar.h"
#include "UI_HpBase.h"
#include "Img_LevUP.h"
#include "Img_LevUP2.h"



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
		mMr->SetMaterial(Resources::Find<Material>(L"AnimationMaterial"));
		mCol->SetCenter(Vector2(0.0f, -2.0f));
		mCol->SetSize(Vector2(0.4f, 0.7f));

		SetChar(SceneManager::GetChar(L"Cheese"));
		mMr->Initialize();
		AddComp<SCRIPT_Player>();
	}
	void Gobj_Player::Update()
	{
		if (mpStat.mLev < 5	&& mpStat.mExp >= nextLevelExp[mpStat.mLev - 1])
		{
			LevelUp();
		}

		if (mpStat.mCurHP > mpStat.mMaxHP)
			mpStat.mCurHP = mpStat.mMaxHP;

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
	void Gobj_Player::Initialize2()
	{
		mpStat = mpChar->GetStat();
		mTr->SetPosition(0.0f, 0.0f, -2.0f);
		std::wstring idle = GetComp<SCRIPT_Player>()->AnimationName(L"Idle");
		mAni->PlayAnimation(idle, true, true);
	}
	void Gobj_Player::LevelUp()
	{
		Vector3 pos0 = mTr->GetPosition();
		pos0.y += 10.0f;
		object::Instantiate<Img_LevUP>(pos0, eLayerType::UI, SceneManager::GetActiveScene());
		object::Instantiate<Img_LevUP2>(eLayerType::Effect, SceneManager::GetActiveScene());

		mpStat.mLev++;
		if (mpStat.mStrength > 25)
			mpStat.mStrength += mpStat.mStrength * 0.25f;
		else if (mpStat.mStrength < 25)
			mpStat.mStrength += mpStat.mStrength * 0.1f;
		mpStat.mDefence += mpStat.mDefence * 0.1f;
		mpStat.mCooldown -= mpStat.mCooldown * 0.1f;
		mpStat.mRange += mpStat.mRange * 0.05f;
		mpStat.mSpeed += mpStat.mSpeed * 0.05f;
		mpStat.mAttackSpeed -= mpStat.mAttackSpeed * 0.05f;
		if (mpStat.mAttackDuration != 0)
			mpStat.mAttackDuration += 0.3f;
		mpStat.mMaxHP += mpStat.mMaxHP * 0.1f;
		mpStat.mCurHP += mpStat.mMaxHP * 0.1f;
		if (mpStat.mLev % 2 == 1)
		{
			if (mpStat.mProjectileCount > 0)
			{
				mpStat.mProjectileCount++;
				mpStat.mDamageScaling = 0.75f;
			}
		}
		mpStat.mExp -= nextLevelExp[mpStat.mLev - 2];
	}
}