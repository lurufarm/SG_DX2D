#include "Melee_SlimeA.h"


namespace sg
{
	Melee_SlimeA::Melee_SlimeA()
	{
		SetName(L"SlimeA");
		Melee_SlimeA::Initialize();
	}
	Melee_SlimeA::~Melee_SlimeA()
	{
	}
	void Melee_SlimeA::Initialize()
	{
		mStat.mHP = 15;
		mStat.mStrength = 2;
		mStat.mSpeed = 30.0f;
		mStat.mRange = 30.0f;
		mStat.dropEXP = 10.0f;

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

		AddComp<SCRIPT_MeleeMob>();
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