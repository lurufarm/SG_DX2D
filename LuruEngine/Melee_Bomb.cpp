#include "Melee_Bomb.h"
#include "SCRIPT_MeleeBomb.h"

namespace sg
{
	Melee_Bomb::Melee_Bomb()
	{
		SetName(L"Bomb");

		mStat.mCurHP = 15;
		mStat.mMaxHP = 15;
		mStat.mStrength = 3;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 30.0f;
		mStat.mRange = 50.0f;
		mStat.mCooldown = 1.0f;
		mStat.dropEXP = 20.0f;

		Melee_Bomb::Initialize();
	}
	Melee_Bomb::~Melee_Bomb()
	{
	}
	void Melee_Bomb::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobBomb");

		mAni->Create(L"Ani_Bomb_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(28.0f, 25.0f), 5, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Bomb_Move", mAtlas->GetTexture(), Vector2(0.0f, 25.0f), Vector2(28.0f, 25.0f), 6, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Bomb_Attack", mAtlas->GetTexture(), Vector2(0.0f, 50.0f), Vector2(28.0f, 25.0f), 9, Vector2::Zero, 0.03f);
		mAni->Create(L"Ani_Bomb_Death", mAtlas->GetTexture(), Vector2(0.0f, 75.0f), Vector2(28.0f, 25.0f), 9, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_Bomb_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 100.0f), Vector2(28.0f, 25.0f), 5, Vector2::Zero, 0.055f);
		mAni->Create(L"Ani_Bomb_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 125.0f), Vector2(28.0f, 25.0f), 10, Vector2::Zero, 0.05f);

		mMr->Initialize();
		mCol->SetSize(Vector2(0.5f, 0.5f));
		mCol->SetCenter(Vector2(0.0f, -2.0f));
		AddComp<SCRIPT_MeleeBomb>();
		Monster_Melee::Initialize();
	}
	void Melee_Bomb::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_Bomb::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_Bomb::Render()
	{
		Monster_Melee::Render();
	}
}