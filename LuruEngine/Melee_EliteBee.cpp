#include "Melee_EliteBee.h"

#include "Melee_Bee.h"
#include "Melee_Bomb.h"
#include "SCRIPT_MeleeBomb.h"

namespace sg
{
	Melee_EliteBee::Melee_EliteBee()
	{
		SetName(L"EliteBee");

		mStat.mCurHP = 100.0f;
		mStat.mMaxHP = 100.0f;
		mStat.mStrength = 2;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 38.0f;
		mStat.mRange = 30.0f;
		mStat.mCooldown = 2.0f;
		mStat.dropEXP = 20.0f;

		Melee_EliteBee::Initialize();
	}
	Melee_EliteBee::~Melee_EliteBee()
	{
	}
	void Melee_EliteBee::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobEliteBee");

		mAni->Create(L"Ani_EliteBee_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(24.0f, 26.0f), 4, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EliteBee_Move", mAtlas->GetTexture(), Vector2::Zero, Vector2(24.0f, 26.0f), 4, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_EliteBee_Attack", mAtlas->GetTexture(), Vector2(0.0f, 26.0f), Vector2(24.0f, 26.0f), 6, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_EliteBee_Death", mAtlas->GetTexture(), Vector2(0.0f, 52.0f), Vector2(24.0f, 26.0f), 9, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_EliteBee_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 78.0f), Vector2(24.0f, 26.0f), 4, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_EliteBee_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 104.0f), Vector2(24.0f, 26.0f), 6, Vector2::Zero, 0.1f);

		mMr->Initialize();
		mCol->SetSize(Vector2(0.5f, 0.5f));
		mCol->SetCenter(Vector2(0.0f, 5.0f));
		AddComp<SCRIPT_MeleeMob>();
		Monster_Melee::Initialize();
	}
	void Melee_EliteBee::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_EliteBee::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_EliteBee::Render()
	{
		Monster_Melee::Render();
	}
}