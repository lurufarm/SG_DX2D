#include "Melee_EliteLarva.h"

namespace sg
{
	Melee_EliteLarva::Melee_EliteLarva()
	{
		SetName(L"EliteLarva");

		mStat.mHP = 75;
		mStat.mStrength = 2;
		mStat.mSpeed = 10.0f;
		mStat.mRange = 10.0f;
		mStat.mCoolDown = 1.5f;
		mStat.dropEXP = 10.0f;

		Melee_EliteLarva::Initialize();
	}
	Melee_EliteLarva::~Melee_EliteLarva()
	{
	}
	void Melee_EliteLarva::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobEliteLarva");

		mAni->Create(L"Ani_EliteLarva_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(24.0f, 20.0f), 6, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EliteLarva_Move", mAtlas->GetTexture(), Vector2(0.0f, 20.0f), Vector2(24.0f, 20.0f), 6, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EliteLarva_Attack", mAtlas->GetTexture(), Vector2(0.0f, 40.0f), Vector2(24.0f, 20.0f), 7, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EliteLarva_Death", mAtlas->GetTexture(), Vector2(0.0f, 60.0f), Vector2(24.0f, 20.0f), 9, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_EliteLarva_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 80.0f), Vector2(24.0f, 20.0f), 6, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_EliteLarva_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 100.0f), Vector2(24.0f, 20.0f), 10, Vector2::Zero, 0.05f);

		mMr->Initialize();
		mCol->SetSize(Vector2(0.8f, 0.5f));
		mCol->SetCenter(Vector2(0.0f, -5.0f));
		AddComp<SCRIPT_MeleeMob>();

		Monster_Melee::Initialize();
	}
	void Melee_EliteLarva::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_EliteLarva::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_EliteLarva::Render()
	{
		Monster_Melee::Render();
	}
}