#include "Melee_Bat.h"

namespace sg
{
	Melee_Bat::Melee_Bat()
	{
		SetName(L"Bat");

		mStat.mCurHP = 15;
		mStat.mMaxHP = 15;
		mStat.mStrength = 3;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 30.0f;
		mStat.mRange = 30.0f;
		mStat.mCooldown = 1.0f;
		mStat.dropEXP = 20.0f;

		Melee_Bat::Initialize();
	}
	Melee_Bat::~Melee_Bat()
	{
	}
	void Melee_Bat::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();
		mCol->SetSize(Vector2(0.5, 0.5f));
		mCol->SetCenter(Vector2(0.0f, 5.0f));

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobBat");

		mAni->Create(L"Ani_Bat_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(29.0f, 31.0f), 5, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Bat_Move", mAtlas->GetTexture(), Vector2::Zero, Vector2(29.0f, 31.0f), 5, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Bat_Attack", mAtlas->GetTexture(), Vector2(0.0f, 31.0f), Vector2(29.0f, 31.0f), 4, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Bat_Death", mAtlas->GetTexture(), Vector2(0.0f, 62.0f), Vector2(29.0f, 31.0f), 9, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_Bat_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 93.0f), Vector2(29.0f, 31.0f), 5, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_Bat_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 124.0f), Vector2(29.0f, 31.0f), 10, Vector2::Zero, 0.05f);

		mMr->Initialize();
		AddComp<SCRIPT_MeleeMob>();
		Monster_Melee::Initialize();
	}
	void Melee_Bat::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_Bat::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_Bat::Render()
	{
		Monster_Melee::Render();
	}
}