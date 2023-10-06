#include "Ranged_MummyBomb.h"
#include "SCRIPT_RangedMob.h"

namespace sg
{
	Ranged_MummyBomb::Ranged_MummyBomb()
	{
		SetName(L"MummyBomb");

		mStat.mCurHP = 32;
		mStat.mMaxHP = 32;
		mStat.mStrength = 4;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 10.0f;
		mStat.mRange = 180.0f;
		mStat.mCooldown = 3.0f;
		mStat.dropEXP = 15.0f;

		Ranged_MummyBomb::Initialize();
	}
	Ranged_MummyBomb::~Ranged_MummyBomb()
	{
	}
	void Ranged_MummyBomb::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobMummyBomb");

		mAni->Create(L"Ani_MummyBomb_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(28.0f, 26.0f), 6, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_MummyBomb_Move", mAtlas->GetTexture(), Vector2(0.0f, 26.0f), Vector2(28.0f, 26.0f), 8, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_MummyBomb_Attack", mAtlas->GetTexture(), Vector2(0.0f, 52.0f), Vector2(28.0f, 26.0f), 11, Vector2::Zero, 0.08f);
		mAni->Create(L"Ani_MummyBomb_Death", mAtlas->GetTexture(), Vector2(0.0f, 78.0f), Vector2(28.0f, 26.0f), 9, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_MummyBomb_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 104.0f), Vector2(28.0f, 26.0f), 5, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_MummyBomb_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 130.0f), Vector2(28.0f, 26.0f), 9, Vector2::Zero, 0.1f);

		mMr->Initialize();
		Monster_Ranged::Initialize();
		AddComp<SCRIPT_RangedMob>();
	}
	void Ranged_MummyBomb::Update()
	{
		Monster_Ranged::Update();
	}
	void Ranged_MummyBomb::LateUpdate()
	{
		Monster_Ranged::LateUpdate();
	}
	void Ranged_MummyBomb::Render()
	{
		Monster_Ranged::Render();
	}
}