#include "Ranged_FireLizard.h"
#include "SCRIPT_RangedMob.h"

namespace sg
{
	Ranged_FireLizard::Ranged_FireLizard()
	{
		SetName(L"FireLizard");

		mStat.mCurHP = 25;
		mStat.mMaxHP = 25;
		mStat.mStrength = 5;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 25.0f;
		mStat.mRange = 80.0f;
		mStat.mCooldown = 3.0f;
		mStat.dropEXP = 20.0f;

		Ranged_FireLizard::Initialize();
	}
	Ranged_FireLizard::~Ranged_FireLizard()
	{
	}
	void Ranged_FireLizard::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobLizard");

		mAni->Create(L"Ani_FireLizard_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(26.0f, 25.0f), 6, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_FireLizard_Move", mAtlas->GetTexture(), Vector2(0.0f, 25.0f), Vector2(26.0f, 25.0f), 7, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_FireLizard_Attack", mAtlas->GetTexture(), Vector2(0.0f, 50.0f), Vector2(26.0f, 25.0f), 12, Vector2::Zero, 0.08f);
		mAni->Create(L"Ani_FireLizard_Death", mAtlas->GetTexture(), Vector2(0.0f, 75.0f), Vector2(26.0f, 25.0f), 9, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_FireLizard_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 100.0f), Vector2(26.0f, 25.0f), 5, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_FireLizard_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 125.0f), Vector2(26.0f, 25.0f), 10, Vector2::Zero, 0.1f);

		mMr->Initialize();
		Monster_Ranged::Initialize();
		AddComp<SCRIPT_RangedMob>();
	}
	void Ranged_FireLizard::Update()
	{
		Monster_Ranged::Update();
	}
	void Ranged_FireLizard::LateUpdate()
	{
		Monster_Ranged::LateUpdate();
	}
	void Ranged_FireLizard::Render()
	{
		Monster_Ranged::Render();
	}
}