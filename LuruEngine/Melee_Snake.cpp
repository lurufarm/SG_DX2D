#include "Melee_Snake.h"

namespace sg
{
	Melee_Snake::Melee_Snake()
	{
		SetName(L"Snake");

		mStat.mCurHP = 20;
		mStat.mMaxHP = 20;
		mStat.mStrength = 3;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 20.0f;
		mStat.mRange = 25.0f;
		mStat.mCooldown = 2.0f;
		mStat.dropEXP = 15.0f;

		Melee_Snake::Initialize();
	}
	Melee_Snake::~Melee_Snake()
	{
	}
	void Melee_Snake::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobSnake");

		mAni->Create(L"Ani_Snake_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(26.0f, 27.0f), 4, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Snake_Move", mAtlas->GetTexture(), Vector2(0.0f, 27.0f), Vector2(26.0f, 27.0f), 6, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Snake_Attack", mAtlas->GetTexture(), Vector2(0.0f, 54.0f), Vector2(26.0f, 27.0f), 4, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Snake_Death", mAtlas->GetTexture(), Vector2(0.0f, 81.0f), Vector2(26.0f, 27.0f), 8, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Snake_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 108.0f), Vector2(26.0f, 27.0f), 4, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Snake_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 135.0f), Vector2(26.0f, 27.0f), 10, Vector2::Zero, 0.1f);

		mMr->Initialize();
		mCol->SetSize(Vector2(0.5f, 0.5f));
		mCol->SetCenter(Vector2(0.0f, -3.0f));
		AddComp<SCRIPT_MeleeMob>();
		Monster_Melee::Initialize();
	}
	void Melee_Snake::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_Snake::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_Snake::Render()
	{
		Monster_Melee::Render();
	}
}