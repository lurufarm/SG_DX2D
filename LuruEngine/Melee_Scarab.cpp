#include "Melee_Scarab.h"

namespace sg
{
	Melee_Scarab::Melee_Scarab()
	{
		SetName(L"Scarab");

		mStat.mCurHP = 15;
		mStat.mMaxHP = 15;
		mStat.mStrength = 2;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 38.0f;
		mStat.mRange = 15.0f;
		mStat.mCooldown = 2.0f;
		mStat.dropEXP = 15.0f;

		Melee_Scarab::Initialize();
	}
	Melee_Scarab::~Melee_Scarab()
	{
	}
	void Melee_Scarab::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobScarab");

		mAni->Create(L"Ani_Scarab_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(26.0f, 25.0f), 4, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Scarab_Move", mAtlas->GetTexture(), Vector2::Zero, Vector2(26.0f, 25.0f), 4, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Scarab_Attack", mAtlas->GetTexture(), Vector2(0.0f, 25.0f), Vector2(26.0f, 25.0f), 5, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Scarab_Death", mAtlas->GetTexture(), Vector2(0.0f, 50.0f), Vector2(26.0f, 25.0f), 9, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Scarab_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 75.0f), Vector2(26.0f, 25.0f), 3, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Scarab_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 100.0f), Vector2(26.0f, 25.0f), 7, Vector2::Zero, 0.1f);

		mMr->Initialize();
		mCol->SetSize(Vector2(0.5f, 0.5f));
		mCol->SetCenter(Vector2(0.0f, 5.0f));
		AddComp<SCRIPT_MeleeMob>();
		Monster_Melee::Initialize();
	}
	void Melee_Scarab::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_Scarab::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_Scarab::Render()
	{
		Monster_Melee::Render();
	}
}