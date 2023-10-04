#include "Melee_EliteBat.h"

namespace sg
{
	Melee_EliteBat::Melee_EliteBat()
	{
		SetName(L"EliteBat");

		mStat.mCurHP = 75;
		mStat.mMaxHP = 75;
		mStat.mStrength = 5;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 30.0f;
		mStat.mRange = 30.0f;
		mStat.mCooldown = 1.0f;
		mStat.dropEXP = 20.0f;

		Melee_EliteBat::Initialize();
	}
	Melee_EliteBat::~Melee_EliteBat()
	{
	}
	void Melee_EliteBat::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();
		mCol->SetSize(Vector2(0.5, 0.5f));
		mCol->SetCenter(Vector2(0.0f, 5.0f));

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobEliteBat");

		mAni->Create(L"Ani_EliteBat_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(29.0f, 31.0f), 5, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EliteBat_Move", mAtlas->GetTexture(), Vector2::Zero, Vector2(29.0f, 31.0f), 5, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EliteBat_Attack", mAtlas->GetTexture(), Vector2(0.0f, 31.0f), Vector2(29.0f, 31.0f), 4, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EliteBat_Death", mAtlas->GetTexture(), Vector2(0.0f, 62.0f), Vector2(29.0f, 31.0f), 9, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_EliteBat_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 93.0f), Vector2(29.0f, 31.0f), 5, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_EliteBat_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 124.0f), Vector2(29.0f, 31.0f), 10, Vector2::Zero, 0.05f);

		mMr->Initialize();
		AddComp<SCRIPT_MeleeMob>();
		Monster_Melee::Initialize();
	}
	void Melee_EliteBat::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_EliteBat::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_EliteBat::Render()
	{
		Monster_Melee::Render();
	}
}