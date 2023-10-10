#include "Melee_Bee.h"

namespace sg
{
	Melee_Bee::Melee_Bee()
	{
		SetName(L"Bee");

		mStat.mCurHP = 20;
		mStat.mMaxHP = 20;
		mStat.mStrength = 2;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 38.0f;
		mStat.mRange = 15.0f;
		mStat.mCooldown = 2.0f;
		mStat.dropEXP = 15.0f;

		Melee_Bee::Initialize();
	}
	Melee_Bee::~Melee_Bee()
	{
	}
	void Melee_Bee::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobBee");

		mAni->Create(L"Ani_Bee_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(24.0f, 26.0f), 4, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Bee_Move", mAtlas->GetTexture(), Vector2::Zero, Vector2(24.0f, 26.0f), 4, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Bee_Attack", mAtlas->GetTexture(), Vector2(0.0f, 26.0f), Vector2(24.0f, 26.0f), 6, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Bee_Death", mAtlas->GetTexture(), Vector2(0.0f, 52.0f), Vector2(24.0f, 26.0f), 9, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Bee_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 78.0f), Vector2(24.0f, 26.0f), 4, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Bee_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 104.0f), Vector2(24.0f, 26.0f), 6, Vector2::Zero, 0.1f);

		mMr->Initialize();
		mCol->SetSize(Vector2(0.5f, 0.5f));
		mCol->SetCenter(Vector2(0.0f, 2.0f));
		AddComp<SCRIPT_MeleeMob>();
		Monster_Melee::Initialize();
	}
	void Melee_Bee::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_Bee::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_Bee::Render()
	{
		Monster_Melee::Render();
	}
}