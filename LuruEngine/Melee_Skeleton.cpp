#include "Melee_Skeleton.h"

namespace sg
{
	Melee_Skeleton::Melee_Skeleton()
	{
		SetName(L"Skeleton");

		mStat.mCurHP = 15;
		mStat.mMaxHP = 15;
		mStat.mStrength = 3;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 30.0f;
		mStat.mRange = 30.0f;
		mStat.mCooldown = 1.0f;
		mStat.dropEXP = 20.0f;

		Melee_Skeleton::Initialize();
	}
	Melee_Skeleton::~Melee_Skeleton()
	{
	}
	void Melee_Skeleton::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();
		mCol->SetSize(Vector2(0.5, 0.5f));
		mCol->SetCenter(Vector2(0.0f, 5.0f));

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobSkeleton");

		mAni->Create(L"Ani_Skeleton_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(28.0f, 24.0f), 6, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Skeleton_Move", mAtlas->GetTexture(), Vector2(0.0f, 24.0f), Vector2(28.0f, 24.0f), 8, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Skeleton_Attack", mAtlas->GetTexture(), Vector2(0.0f, 48.0f), Vector2(28.0f, 24.0f), 6, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Skeleton_Death", mAtlas->GetTexture(), Vector2(0.0f, 72.0f), Vector2(28.0f, 24.0f), 10, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_Skeleton_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 96.0f), Vector2(28.0f, 24.0f), 7, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_Skeleton_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 120.0f), Vector2(28.0f, 24.0f), 10, Vector2::Zero, 0.05f);

		mMr->Initialize();
		AddComp<SCRIPT_MeleeMob>();
		Monster_Melee::Initialize();
	}
	void Melee_Skeleton::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_Skeleton::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_Skeleton::Render()
	{
		Monster_Melee::Render();
	}
}