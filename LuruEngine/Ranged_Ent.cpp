#include "Ranged_Ent.h"
#include "SCRIPT_RangedMob.h"

namespace sg
{
	Ranged_Ent::Ranged_Ent()
	{
		SetName(L"Ent");

		mStat.mCurHP = 32;
		mStat.mMaxHP = 32;
		mStat.mStrength = 4;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 10.0f;
		mStat.mRange = 180.0f;
		mStat.mCooldown = 3.0f;
		mStat.dropEXP = 15.0f;

		Ranged_Ent::Initialize();
	}
	Ranged_Ent::~Ranged_Ent()
	{
	}
	void Ranged_Ent::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobEnt");

		mAni->Create(L"Ani_Ent_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(35.0f, 32.0f), 6, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Ent_Move", mAtlas->GetTexture(), Vector2(0.0f, 32.0f), Vector2(35.0f, 32.0f), 6, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Ent_Attack", mAtlas->GetTexture(), Vector2(0.0f, 64.0f), Vector2(35.0f, 32.0f), 9, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Ent_Death", mAtlas->GetTexture(), Vector2(0.0f, 96.0f), Vector2(35.0f, 32.0f), 7, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Ent_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 128.0f), Vector2(35.0f, 32.0f), 6, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Ent_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 160.0f), Vector2(35.0f, 32.0f), 10, Vector2::Zero, 0.1f);

		mMr->Initialize();
		Monster_Ranged::Initialize();
		AddComp<SCRIPT_RangedMob>();
	}
	void Ranged_Ent::Update()
	{
		Monster_Ranged::Update();
	}
	void Ranged_Ent::LateUpdate()
	{
		Monster_Ranged::LateUpdate();
	}
	void Ranged_Ent::Render()
	{
		Monster_Ranged::Render();
	}
}