#include "Ranged_CannibalFlowerA.h"
#include "SCRIPT_RangedMob.h"

namespace sg
{
	Ranged_CannibalFlowerA::Ranged_CannibalFlowerA()
	{
		SetName(L"CannibalFlowerA");

		mStat.mHP = 18;
		mStat.mStrength = 3;
		mStat.mSpeed = 10.0f;
		mStat.mRange = 60.0f;
		mStat.dropEXP = 10.0f;

		Ranged_CannibalFlowerA::Initialize();
	}
	Ranged_CannibalFlowerA::~Ranged_CannibalFlowerA()
	{
	}
	void Ranged_CannibalFlowerA::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobCannibalFlowerA");

		mAni->Create(L"Ani_CannibalFlowerA_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(23.0f, 25.0f), 7, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_CannibalFlowerA_Move", mAtlas->GetTexture(), Vector2(0.0f, 25.0f), Vector2(23.0f, 25.0f), 7, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_CannibalFlowerA_Attack", mAtlas->GetTexture(), Vector2(0.0f, 50.0f), Vector2(23.0f, 25.0f), 7, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_CannibalFlowerA_Death", mAtlas->GetTexture(), Vector2(0.0f, 75.0f), Vector2(23.0f, 25.0f), 7, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_CannibalFlowerA_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 100.0f), Vector2(23.0f, 25.0f), 7, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_CannibalFlowerA_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 125.0f), Vector2(23.0f, 25.0f), 10, Vector2::Zero, 0.05f);

		mMr->Initialize();
		//mCol->SetSize(Vector2(0.5f, 0.5f));
		AddComp<SCRIPT_RangedMob>();
	}
	void Ranged_CannibalFlowerA::Update()
	{
		Monster_Ranged::Update();
	}
	void Ranged_CannibalFlowerA::LateUpdate()
	{
		Monster_Ranged::LateUpdate();
	}
	void Ranged_CannibalFlowerA::Render()
	{
		Monster_Ranged::Render();
	}
}