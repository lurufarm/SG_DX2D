#include "Melee_Cannibals.h"

namespace sg
{
	Melee_Cannibals::Melee_Cannibals()
	{
		SetName(L"Cannibals");

		mStat.mCurHP = 25;
		mStat.mStrength = 3;
		mStat.mSpeed = 20.0f;
		mStat.mRange = 10.0f;
		mStat.mCooldown = 1.0f;
		mStat.dropEXP = 10.0f;

		Melee_Cannibals::Initialize();
	}
	Melee_Cannibals::~Melee_Cannibals()
	{
	}
	void Melee_Cannibals::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobCannibals");

		mAni->Create(L"Ani_Cannibals_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(28.0f, 26.0f), 6, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Cannibals_Move", mAtlas->GetTexture(), Vector2(0.0f, 26.0f), Vector2(28.0f, 26.0f), 8, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Cannibals_Attack", mAtlas->GetTexture(), Vector2(0.0f, 52.0f), Vector2(28.0f, 26.0f), 7, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Cannibals_Death", mAtlas->GetTexture(), Vector2(0.0f, 78.0f), Vector2(28.0f, 26.0f), 8, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_Cannibals_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 104.0f), Vector2(28.0f, 26.0f), 5, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_Cannibals_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 130.0f), Vector2(28.0f, 26.0f), 10, Vector2::Zero, 0.05f);

		mMr->Initialize();
		mCol->SetSize(Vector2(0.8f, 0.5f));
		//mCol->SetCenter(Vector2(0.0f, -5.0f));
		AddComp<SCRIPT_MeleeMob>();

		Monster_Melee::Initialize();
	}
	void Melee_Cannibals::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_Cannibals::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_Cannibals::Render()
	{
		Monster_Melee::Render();
	}
}