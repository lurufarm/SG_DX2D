#include "Melee_Larva.h"

namespace sg
{
	Melee_Larva::Melee_Larva()
	{
		SetName(L"Larva");

		mStat.mCurHP = 15;
		mStat.mStrength = 3;
		mStat.mSpeed = 10.0f;
		mStat.mRange = 10.0f;
		mStat.mCooldown = 1.5f;
		mStat.dropEXP = 10.0f;

		Melee_Larva::Initialize();
	}
	Melee_Larva::~Melee_Larva()
	{
	}
	void Melee_Larva::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobLarva");

		mAni->Create(L"Ani_Larva_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(24.0f, 20.0f), 6, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Larva_Move", mAtlas->GetTexture(), Vector2(0.0f, 20.0f), Vector2(24.0f, 20.0f), 6, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Larva_Attack", mAtlas->GetTexture(), Vector2(0.0f, 40.0f), Vector2(24.0f, 20.0f), 7, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Larva_Death", mAtlas->GetTexture(), Vector2(0.0f, 60.0f), Vector2(24.0f, 20.0f), 9, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_Larva_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 80.0f), Vector2(24.0f, 20.0f), 6, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_Larva_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 100.0f), Vector2(24.0f, 20.0f), 10, Vector2::Zero, 0.05f);

		mMr->Initialize();
		mCol->SetSize(Vector2(0.8f, 0.5f));
		mCol->SetCenter(Vector2(0.0f, -5.0f));
		AddComp<SCRIPT_MeleeMob>();

		Monster_Melee::Initialize();
	}
	void Melee_Larva::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_Larva::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_Larva::Render()
	{
		Monster_Melee::Render();
	}
}