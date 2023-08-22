#include "Boss_OldEnt.h"
#include "SCRIPT_RangedMob.h"
#include "SCRIPT_Boss.h"

namespace sg
{
	Boss_OldEnt::Boss_OldEnt()
	{
		SetName(L"OldEnt");

		mStat.mHP = 225;
		mStat.mStrength = 4;
		mStat.mSpeed = 10.0f;
		mStat.mRange = 180.0f;
		mStat.mCoolDown = 2.3f;
		mStat.dropEXP = 15.0f;

		Boss_OldEnt::Initialize();
	}
	Boss_OldEnt::~Boss_OldEnt()
	{
	}
	void Boss_OldEnt::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobOldEnt");

		mAni->Create(L"Ani_OldEnt_Spawn", mAtlas->GetTexture(), Vector2::Zero, Vector2(43.0f, 47.0f), 13, Vector2::Zero, 0.07f);
		mAni->Create(L"Ani_OldEnt_Idle", mAtlas->GetTexture(), Vector2(0.0f, 47.0f), Vector2(43.0f, 47.0f), 6, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_OldEnt_Move", mAtlas->GetTexture(), Vector2(0.0f, 94.0f), Vector2(43.0f, 47.0f), 7, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_OldEnt_Attack", mAtlas->GetTexture(), Vector2(0.0f, 141.0f), Vector2(43.0f, 47.0f), 9, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_OldEnt_Attack2", mAtlas->GetTexture(), Vector2(0.0f, 188.0f), Vector2(43.0f, 47.0f), 18, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_OldEnt_Death", mAtlas->GetTexture(), Vector2(0.0f, 235.0f), Vector2(43.0f, 47.0f), 10, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_OldEnt_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 282.0f), Vector2(43.0f, 47.0f), 7, Vector2::Zero, 0.1f);

		mMr->Initialize();
		Monster_Ranged::Initialize();
		AddComp<SCRIPT_Boss>();
	}
	void Boss_OldEnt::Update()
	{
		Monster_Ranged::Update();
	}
	void Boss_OldEnt::LateUpdate()
	{
		Monster_Ranged::LateUpdate();
	}
	void Boss_OldEnt::Render()
	{
		Monster_Ranged::Render();
	}
}