#include "Melee_EliteCannibals.h"

namespace sg
{
	Melee_EliteCannibals::Melee_EliteCannibals()
	{
		SetName(L"EliteCannibals");

		mStat.mCurHP = 125;
		mStat.mMaxHP = 125;
		mStat.mStrength = 5;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 25.0f;
		mStat.mRange = 10.0f;
		mStat.mCooldown = 1.0f;
		mStat.dropEXP = 20.0f;

		Melee_EliteCannibals::Initialize();
	}
	Melee_EliteCannibals::~Melee_EliteCannibals()
	{
	}
	void Melee_EliteCannibals::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobEliteCannibals");

		mAni->Create(L"Ani_EliteCannibals_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(28.0f, 26.0f), 6, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EliteCannibals_Move", mAtlas->GetTexture(), Vector2(0.0f, 26.0f), Vector2(28.0f, 26.0f), 7, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EliteCannibals_Attack", mAtlas->GetTexture(), Vector2(0.0f, 52.0f), Vector2(28.0f, 26.0f), 8, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EliteCannibals_Death", mAtlas->GetTexture(), Vector2(0.0f, 78.0f), Vector2(28.0f, 26.0f), 8, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_EliteCannibals_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 104.0f), Vector2(28.0f, 26.0f), 5, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_EliteCannibals_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 130.0f), Vector2(28.0f, 26.0f), 7, Vector2::Zero, 0.05f);

		mMr->Initialize();
		mCol->SetSize(Vector2(0.8f, 0.5f));
		//mCol->SetCenter(Vector2(0.0f, -5.0f));
		AddComp<SCRIPT_MeleeMob>();

		Monster_Melee::Initialize();
	}
	void Melee_EliteCannibals::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_EliteCannibals::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_EliteCannibals::Render()
	{
		Monster_Melee::Render();
	}
}