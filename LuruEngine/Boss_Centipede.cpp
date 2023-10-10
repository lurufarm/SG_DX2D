#include "Boss_Centipede.h"
#include "Gobj_Monster.h"
#include "Monster_Ranged.h"
#include "SCRIPT_Centipede.h"

namespace sg
{
	Boss_Centipede::Boss_Centipede()
	{
		SetName(L"Centipede");

		mStat.mCurHP = 225;
		mStat.mMaxHP = 225;
		mStat.mStrength = 7;
		mStat.mDefence = 0.3f;
		mStat.mSpeed = 10.0f;
		mStat.mRange = 180.0f;
		mStat.mCooldown = 2.3f;
		mStat.dropEXP = 20.0f;

		Boss_Centipede::Initialize();
	}
	Boss_Centipede::~Boss_Centipede()
	{
	}
	void Boss_Centipede::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobCentipede");

		mAni->Create(L"Ani_Centipede_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 164.0f), Vector2(62.0f, 82.0f), 9, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Centipede_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(62.0f, 82.0f), 8, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Centipede_Move1", mAtlas->GetTexture(), Vector2(0.0f, 82.0f), Vector2(62.0f, 82.0f), 10, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Centipede_Move2", mAtlas->GetTexture(), Vector2(0.0f, 164.0f), Vector2(62.0f, 82.0f), 9, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Centipede_Attack", mAtlas->GetTexture(), Vector2(0.0f, 246.0f), Vector2(62.0f, 82.0f), 13, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Centipede_Attack2", mAtlas->GetTexture(), Vector2(0.0f, 328.0f), Vector2(62.0f, 82.0f), 13, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Centipede_Attack3", mAtlas->GetTexture(), Vector2(0.0f, 410.0f), Vector2(62.0f, 82.0f), 6, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Centipede_Death", mAtlas->GetTexture(), Vector2(0.0f, 492.0f), Vector2(62.0f, 82.0f), 12, Vector2::Zero, 0.08f);

		mMr->Initialize();
		mCol->SetCenter(Vector2(0.0f, -5.0f));
		mCol->SetSize(Vector2(0.5f, 0.6f));
		AddComp<SCRIPT_Centipede>();
		Gobj_Monster::Initialize();
	}
	void Boss_Centipede::Update()
	{
		Gobj_Monster::Update();
	}
	void Boss_Centipede::LateUpdate()
	{
		Gobj_Monster::LateUpdate();
	}
	void Boss_Centipede::Render()
	{
		Gobj_Monster::Render();
	}
}