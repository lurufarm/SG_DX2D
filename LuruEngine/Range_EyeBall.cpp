#include "Range_EyeBall.h"
#include "SCRIPT_RangedMob.h"

namespace sg
{
	Range_EyeBall::Range_EyeBall()
	{
		SetName(L"EyeBall");

		mStat.mCurHP = 18;
		mStat.mMaxHP = 18;
		mStat.mStrength = 4;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 10.0f;
		mStat.mRange = 100.0f;
		mStat.mCooldown = 2.0f;
		mStat.dropEXP = 10.0f;

		Range_EyeBall::Initialize();
	}
	Range_EyeBall::~Range_EyeBall()
	{
	}
	void Range_EyeBall::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobCannibalFlowerA");

		mAni->Create(L"Ani_EyeBall_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(23.0f, 25.0f), 7, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_EyeBall_Move", mAtlas->GetTexture(), Vector2(0.0f, 25.0f), Vector2(23.0f, 25.0f), 7, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_EyeBall_Attack", mAtlas->GetTexture(), Vector2(0.0f, 50.0f), Vector2(23.0f, 25.0f), 7, Vector2::Zero, 0.15f);
		mAni->Create(L"Ani_EyeBall_Death", mAtlas->GetTexture(), Vector2(0.0f, 75.0f), Vector2(23.0f, 25.0f), 7, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_EyeBall_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 100.0f), Vector2(23.0f, 25.0f), 5, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_EyeBall_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 125.0f), Vector2(23.0f, 25.0f), 10, Vector2::Zero, 0.1f);

		mMr->Initialize();
		Monster_Ranged::Initialize();
		AddComp<SCRIPT_RangedMob>();
	}
	void Range_EyeBall::Update()
	{
		Monster_Ranged::Update();
	}
	void Range_EyeBall::LateUpdate()
	{
		Monster_Ranged::LateUpdate();
	}
	void Range_EyeBall::Render()
	{
		Monster_Ranged::Render();
	}
}