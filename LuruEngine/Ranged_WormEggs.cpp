#include "Ranged_WormEggs.h"
#include "SCRIPT_RangedMob.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "monsters.h"

namespace sg
{
	Ranged_WormEggs::Ranged_WormEggs()
	{
		SetName(L"WormEggs");

		mStat.mCurHP = 35;
		mStat.mMaxHP = 35;
		mStat.mStrength = 0.0f;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 0.0f;
		mStat.mRange = 1000.0f;
		mStat.mCooldown = 5.0f;
		mStat.dropEXP = 20.0f;

		Ranged_WormEggs::Initialize();
	}
	Ranged_WormEggs::~Ranged_WormEggs()
	{
	}
	void Ranged_WormEggs::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobWormEggs");

		mAni->Create(L"Ani_WormEggs_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(28.0f, 29.0f), 2, Vector2::Zero, 1.0f);
		mAni->Create(L"Ani_WormEggs_Move", mAtlas->GetTexture(), Vector2::Zero, Vector2(28.0f, 29.0f), 2, Vector2::Zero, 1.0f);
		mAni->Create(L"Ani_WormEggs_Attack", mAtlas->GetTexture(), Vector2(0.0f, 29.0f), Vector2(28.0f, 29.0f), 7, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_WormEggs_Death", mAtlas->GetTexture(), Vector2(0.0f, 58.0f), Vector2(28.0f, 29.0f), 7, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_WormEggs_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 87.0f), Vector2(28.0f, 29.0f), 2, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_WormEggs_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 116.0f), Vector2(28.0f, 29.0f), 8, Vector2::Zero, 0.1f);

		mMr->Initialize();
		mCol->SetSize(Vector2(0.5f, 0.5f));
		mCol->SetCenter(Vector2(0.0f, 5.0f));

		mLaunched = false;

		mAni->PlayAnimation(L"Ani_WormEggs_Spawn", false, false);
		AddComp<SCRIPT_RangedMob>();
		Monster_Ranged::Initialize();
	}
	void Ranged_WormEggs::Update()
	{
		int Index = mAni->GetActiveAni()->GetAniIndex();
		std::wstring aniName = mAni->GetActiveAni()->GetKey();
		if (Index == 6
			&& aniName == L"Ani_WormEggs_Attack"
			&& mLaunched == false)
		{
			Vector3 ownerPos = GetComp<Transform>()->GetPosition();
			object::Instantiate<Melee_Scarab>(sgRandomPos(ownerPos, 30.0f), eLayerType::Monster, SceneManager::GetActiveScene());
			object::Instantiate<Melee_Scarab>(sgRandomPos(ownerPos, 30.0f), eLayerType::Monster, SceneManager::GetActiveScene());
			object::Instantiate<Melee_Scarab>(sgRandomPos(ownerPos, 30.0f), eLayerType::Monster, SceneManager::GetActiveScene());
			mLaunched = true;
		}
		if (aniName != L"Ani_WormEggs_Attack")
			mLaunched = false;

		Monster_Ranged::Update();
	}
	void Ranged_WormEggs::LateUpdate()
	{
		Monster_Ranged::LateUpdate();
	}
	void Ranged_WormEggs::Render()
	{
		Monster_Ranged::Render();
	}
}