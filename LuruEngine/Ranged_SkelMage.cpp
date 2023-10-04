#include "Ranged_SkelMage.h"
#include "SCRIPT_RangedMob.h"

namespace sg
{
	Ranged_SkelMage::Ranged_SkelMage()
	{
		SetName(L"SkelMage");

		mStat.mCurHP = 22;
		mStat.mMaxHP = 22;
		mStat.mStrength = 4;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 20.0f;
		mStat.mRange = 180.0f;
		mStat.mCooldown = 3.0f;
		mStat.dropEXP = 15.0f;

		Ranged_SkelMage::Initialize();
	}
	Ranged_SkelMage::~Ranged_SkelMage()
	{
	}
	void Ranged_SkelMage::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobSkelMage");

		mAni->Create(L"Ani_SkelMage_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(28.0f, 26.0f), 7, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_SkelMage_Move", mAtlas->GetTexture(), Vector2(0.0f, 26.0f), Vector2(28.0f, 26.0f), 7, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_SkelMage_Attack", mAtlas->GetTexture(), Vector2(0.0f, 52.0f), Vector2(28.0f, 26.0f), 7, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_SkelMage_Death", mAtlas->GetTexture(), Vector2(0.0f, 78.0f), Vector2(28.0f, 26.0f), 10, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_SkelMage_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 104.0f), Vector2(28.0f, 26.0f), 7, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_SkelMage_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 130.0f), Vector2(28.0f, 26.0f), 10, Vector2::Zero, 0.1f);

		mMr->Initialize();
		Monster_Ranged::Initialize();
		AddComp<SCRIPT_RangedMob>();
	}
	void Ranged_SkelMage::Update()
	{
		Monster_Ranged::Update();
	}
	void Ranged_SkelMage::LateUpdate()
	{
		Monster_Ranged::LateUpdate();
	}
	void Ranged_SkelMage::Render()
	{
		Monster_Ranged::Render();
	}
}