#include "Melee_MummyPoison.h"
#include "SCRIPT_MeleeMummyPoison.h"
#include "Effect_PoisionExplosion.h"
#include "..\Engine_SOURCE\sgObject.h"

namespace sg
{
	Melee_MummyPoison::Melee_MummyPoison()
	{
		SetName(L"MummyPoison");

		mStat.mCurHP = 20;
		mStat.mMaxHP = 20;
		mStat.mStrength = 2;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 35.0f;
		mStat.mRange = 35.0f;
		mStat.mCooldown = 2.0f;
		mStat.dropEXP = 18.0f;

		Melee_MummyPoison::Initialize();
	}
	Melee_MummyPoison::~Melee_MummyPoison()
	{
		object::Instantiate<Effect_PoisionExplosion>(mTr->GetPosition(), eLayerType::Effect, SceneManager::GetActiveScene());
	}
	void Melee_MummyPoison::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobMummyPoison");

		mAni->Create(L"Ani_MummyPoison_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(27.0f, 26.0f), 6, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_MummyPoison_Move", mAtlas->GetTexture(), Vector2(0.0f, 26.0f), Vector2(27.0f, 26.0f), 8, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_MummyPoison_Attack", mAtlas->GetTexture(), Vector2(0.0f, 52.0f), Vector2(27.0f, 26.0f), 16, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_MummyPoison_Death", mAtlas->GetTexture(), Vector2(0.0f, 78.0f), Vector2(27.0f, 26.0f), 10, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_MummyPoison_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 104.0f), Vector2(27.0f, 26.0f), 7, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_MummyPoison_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 130.0f), Vector2(27.0f, 26.0f), 10, Vector2::Zero, 0.05f);

		mMr->Initialize();
		AddComp<SCRIPT_MeleeMummyPoison>();
		Monster_Melee::Initialize();
	}
	void Melee_MummyPoison::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_MummyPoison::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_MummyPoison::Render()
	{
		Monster_Melee::Render();
	}
}