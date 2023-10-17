#include "Melee_SlimeA.h"


namespace sg
{
	Melee_SlimeA::Melee_SlimeA()
	{
		SetName(L"SlimeA");

		mStat.mCurHP = 15;
		mStat.mMaxHP = 15;
		mStat.mStrength = 2;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 10.0f;
		mStat.mRange = 10.0f;
		mStat.mCooldown = 2.0f;
		mStat.dropEXP = 10.0f;

		Melee_SlimeA::Initialize();
	}
	Melee_SlimeA::~Melee_SlimeA()
	{
	}
	void Melee_SlimeA::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobSlimeA");

		mAni->Create(L"Ani_SlimeA_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(24.0f, 22.0f), 7, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_SlimeA_Move", mAtlas->GetTexture(), Vector2(0.0f, 22.0f), Vector2(24.0f, 22.0f), 7, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_SlimeA_Attack", mAtlas->GetTexture(), Vector2(0.0f, 44.0f), Vector2(24.0f, 22.0f), 7, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_SlimeA_Death", mAtlas->GetTexture(), Vector2(0.0f, 66.0f), Vector2(24.0f, 22.0f), 7, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_SlimeA_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 88.0f), Vector2(24.0f, 22.0f), 7, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_SlimeA_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 110.0f), Vector2(24.0f, 22.0f), 10, Vector2::Zero, 0.05f);

		mMr->Initialize();
		mCol->SetSize(Vector2(0.8f, 0.8f));
		mCol->SetCenter(Vector2(0.0f, -5.0f));
		AddComp<SCRIPT_MeleeMob>();

		Monster_Melee::Initialize();
	}
	void Melee_SlimeA::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_SlimeA::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_SlimeA::Render()
	{
		Monster_Melee::Render();
	}
}