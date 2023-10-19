#include "Ranged_Janubis.h"
#include "SCRIPT_RangedMob.h"

namespace sg
{
	Ranged_Janubis::Ranged_Janubis()
	{
		SetName(L"Janubis");

		mStat.mCurHP = 50;
		mStat.mMaxHP = 50;
		mStat.mStrength = 5;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 25.0f;
		mStat.mRange = 80.0f;
		mStat.mCooldown = 3.0f;
		mStat.dropEXP = 20.0f;

		Ranged_Janubis::Initialize();
	}
	Ranged_Janubis::~Ranged_Janubis()
	{
	}
	void Ranged_Janubis::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobJanubis");

		mAni->Create(L"Ani_Janubis_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(28.0f, 26.0f), 6, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Janubis_Move", mAtlas->GetTexture(), Vector2(0.0f, 26.0f), Vector2(28.0f, 26.0f), 8, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Janubis_Attack", mAtlas->GetTexture(), Vector2(0.0f, 52.0f), Vector2(28.0f, 26.0f), 6, Vector2::Zero, 0.08f);
		mAni->Create(L"Ani_Janubis_Death", mAtlas->GetTexture(), Vector2(0.0f, 78.0f), Vector2(28.0f, 26.0f), 10, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Janubis_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 104.0f), Vector2(28.0f, 26.0f), 6, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Janubis_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 130.0f), Vector2(28.0f, 26.0f), 10, Vector2::Zero, 0.1f);

		mMr->Initialize();
		Monster_Ranged::Initialize();
		AddComp<SCRIPT_RangedMob>();
	}
	void Ranged_Janubis::Update()
	{
		Monster_Ranged::Update();
	}
	void Ranged_Janubis::LateUpdate()
	{
		Monster_Ranged::LateUpdate();
	}
	void Ranged_Janubis::Render()
	{
		Monster_Ranged::Render();
	}
}