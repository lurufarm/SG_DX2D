#include "Melee_SlimeB.h"


namespace sg
{
	Melee_SlimeB::Melee_SlimeB()
	{
		SetName(L"SlimeB");

		mStat.mCurHP = 25;
		mStat.mMaxHP = 25;
		mStat.mStrength = 3;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 20.0f;
		mStat.mRange = 30.0f;
		mStat.mCooldown = 1.0f;
		mStat.dropEXP = 15.0f;

		Melee_SlimeB::Initialize();
	}
	Melee_SlimeB::~Melee_SlimeB()
	{
	}
	void Melee_SlimeB::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobSlimeB");

		mAni->Create(L"Ani_SlimeB_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(25.0f, 25.0f), 7, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_SlimeB_Move", mAtlas->GetTexture(), Vector2(0.0f, 25.0f), Vector2(25.0f, 25.0f), 7, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_SlimeB_Attack", mAtlas->GetTexture(), Vector2(0.0f, 50.0f), Vector2(25.0f, 25.0f), 7, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_SlimeB_Death", mAtlas->GetTexture(), Vector2(0.0f, 75.0f), Vector2(25.0f, 25.0f), 7, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_SlimeB_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 100.0f), Vector2(25.0f, 25.0f), 7, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_SlimeB_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 125.0f), Vector2(25.0f, 25.0f), 10, Vector2::Zero, 0.05f);

		mMr->Initialize();
		mCol->SetSize(Vector2(0.5f, 0.5f));
		AddComp<SCRIPT_MeleeMob>();
		Monster_Melee::Initialize();
	}
	void Melee_SlimeB::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_SlimeB::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_SlimeB::Render()
	{
		Monster_Melee::Render();
	}
}