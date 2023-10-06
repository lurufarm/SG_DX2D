#include "Melee_Mummy.h"

namespace sg
{
	Melee_Mummy::Melee_Mummy()
	{
		SetName(L"Mummy");

		mStat.mCurHP = 20;
		mStat.mMaxHP = 20;
		mStat.mStrength = 2;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 35.0f;
		mStat.mRange = 35.0f;
		mStat.mCooldown = 2.0f;
		mStat.dropEXP = 18.0f;

		Melee_Mummy::Initialize();
	}
	Melee_Mummy::~Melee_Mummy()
	{
	}
	void Melee_Mummy::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobMummy");

		mAni->Create(L"Ani_Mummy_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(27.0f, 26.0f), 6, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Mummy_Move", mAtlas->GetTexture(), Vector2(0.0f, 26.0f), Vector2(27.0f, 26.0f), 8, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Mummy_Attack", mAtlas->GetTexture(), Vector2(0.0f, 52.0f), Vector2(27.0f, 26.0f), 6, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Mummy_Death", mAtlas->GetTexture(), Vector2(0.0f, 78.0f), Vector2(27.0f, 26.0f), 10, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Mummy_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 104.0f), Vector2(27.0f, 26.0f), 7, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Mummy_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 130.0f), Vector2(27.0f, 26.0f), 10, Vector2::Zero, 0.05f);

		mMr->Initialize();
		mCol->SetSize(Vector2(0.5f, 0.5f));
		AddComp<SCRIPT_MeleeMob>();
		Monster_Melee::Initialize();
	}
	void Melee_Mummy::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_Mummy::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_Mummy::Render()
	{
		Monster_Melee::Render();
	}
}