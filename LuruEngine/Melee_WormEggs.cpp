#include "Melee_WormEggs.h"

namespace sg
{
	Melee_WormEggs::Melee_WormEggs()
	{
		SetName(L"WormEggs");

		mStat.mCurHP = 35;
		mStat.mMaxHP = 35;
		mStat.mStrength = 0.0f;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 0.0f;
		mStat.mRange = 0.0f;
		mStat.mCooldown = 3.0f;
		mStat.dropEXP = 20.0f;

		Melee_WormEggs::Initialize();
	}
	Melee_WormEggs::~Melee_WormEggs()
	{
	}
	void Melee_WormEggs::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobWormEggs");

		mAni->Create(L"Ani_WormEggs_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(28.0f, 29.0f), 2, Vector2::Zero, 1.0f);
		mAni->Create(L"Ani_WormEggs_Move", mAtlas->GetTexture(), Vector2::Zero, Vector2(28.0f, 29.0f), 2, Vector2::Zero, 1.0f);
		mAni->Create(L"Ani_WormEggs_Attack", mAtlas->GetTexture(), Vector2(0.0f, 29.0f), Vector2(28.0f, 29.0f), 7, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_WormEggs_Death", mAtlas->GetTexture(), Vector2(0.0f, 58.0f), Vector2(28.0f, 29.0f), 7, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_WormEggs_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 87.0f), Vector2(28.0f, 29.0f), 2, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_WormEggs_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 116.0f), Vector2(28.0f, 29.0f), 8, Vector2::Zero, 0.1f);

		mMr->Initialize();
		mCol->SetSize(Vector2(0.5f, 0.5f));
		mCol->SetCenter(Vector2(0.0f, 5.0f));
		AddComp<SCRIPT_MeleeMob>();
		Monster_Melee::Initialize();
	}
	void Melee_WormEggs::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_WormEggs::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_WormEggs::Render()
	{
		Monster_Melee::Render();
	}
}