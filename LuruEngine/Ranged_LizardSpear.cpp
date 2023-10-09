#include "Ranged_LizardSpear.h"
#include "SCRIPT_RangedMob.h"

namespace sg
{
	Ranged_LizardSpear::Ranged_LizardSpear()
	{
		SetName(L"LizardSpear");

		mStat.mCurHP = 25;
		mStat.mMaxHP = 25;
		mStat.mStrength = 5;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 25.0f;
		mStat.mRange = 80.0f;
		mStat.mCooldown = 3.0f;
		mStat.dropEXP = 20.0f;

		Ranged_LizardSpear::Initialize();
	}
	Ranged_LizardSpear::~Ranged_LizardSpear()
	{
	}
	void Ranged_LizardSpear::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobLizardSpear");

		mAni->Create(L"Ani_LizardSpear_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(31.0f, 25.0f), 6, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_LizardSpear_Move", mAtlas->GetTexture(), Vector2(0.0f, 25.0f), Vector2(31.0f, 25.0f), 8, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_LizardSpear_Attack", mAtlas->GetTexture(), Vector2(0.0f, 50.0f), Vector2(31.0f, 25.0f), 13, Vector2::Zero, 0.08f);
		mAni->Create(L"Ani_LizardSpear_Death", mAtlas->GetTexture(), Vector2(0.0f, 75.0f), Vector2(31.0f, 25.0f), 9, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_LizardSpear_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 100.0f), Vector2(31.0f, 25.0f), 4, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_LizardSpear_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 125.0f), Vector2(31.0f, 25.0f), 9, Vector2::Zero, 0.1f);

		mMr->Initialize();
		Monster_Ranged::Initialize();
		AddComp<SCRIPT_RangedMob>();
	}
	void Ranged_LizardSpear::Update()
	{
		Monster_Ranged::Update();
	}
	void Ranged_LizardSpear::LateUpdate()
	{
		Monster_Ranged::LateUpdate();
	}
	void Ranged_LizardSpear::Render()
	{
		Monster_Ranged::Render();
	}
}