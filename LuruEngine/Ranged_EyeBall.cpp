#include "Ranged_EyeBall.h"
#include "SCRIPT_RangedMob.h"

namespace sg
{
	Ranged_EyeBall::Ranged_EyeBall()
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

		Ranged_EyeBall::Initialize();
	}
	Ranged_EyeBall::~Ranged_EyeBall()
	{
	}
	void Ranged_EyeBall::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobEyeBall");

		mAni->Create(L"Ani_EyeBall_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(28.0f, 28.0f), 4, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_EyeBall_Move", mAtlas->GetTexture(), Vector2(0.0f, 28.0f), Vector2(28.0f, 28.0f), 6, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_EyeBall_Attack", mAtlas->GetTexture(), Vector2(0.0f, 56.0f), Vector2(28.0f, 28.0f), 6, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_EyeBall_Death", mAtlas->GetTexture(), Vector2(0.0f, 84.0f), Vector2(28.0f, 28.0f), 15, Vector2::Zero, 0.07f);
		mAni->Create(L"Ani_EyeBall_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 112.0f), Vector2(28.0f, 28.0f), 5, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_EyeBall_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 140.0f), Vector2(28.0f, 28.0f), 10, Vector2::Zero, 0.1f);

		mMr->Initialize();
		Monster_Ranged::Initialize();
		AddComp<SCRIPT_RangedMob>();
	}
	void Ranged_EyeBall::Update()
	{
		Monster_Ranged::Update();
	}
	void Ranged_EyeBall::LateUpdate()
	{
		Monster_Ranged::LateUpdate();
	}
	void Ranged_EyeBall::Render()
	{
		Monster_Ranged::Render();
	}
}