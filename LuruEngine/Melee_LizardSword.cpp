#include "Melee_LizardSword.h"
#include "SCRIPT_MeleeMob.h"

namespace sg
{
	Melee_LizardSword::Melee_LizardSword()
	{
		SetName(L"LizardSword");

		mStat.mCurHP = 20.0f;
		mStat.mMaxHP = 20.0f;
		mStat.mStrength = 5;
		mStat.mDefence = 0.0f;
		mStat.mSpeed = 30.0f;
		mStat.mRange = 20.0f;
		mStat.mCooldown = 2.0f;
		mStat.dropEXP = 20.0f;

		Melee_LizardSword::Initialize();
	}
	Melee_LizardSword::~Melee_LizardSword()
	{
	}
	void Melee_LizardSword::Initialize()
	{
		mTr = GetComp<Transform>();
		mMr = GetComp<MeshRenderer>();
		mCol = GetComp<Collider2D>();
		mAni = GetComp<Animator>();

		SetMesh();
		SetMaterial(L"AnimationMaterial");

		mAtlas = Resources::Find<Material>(L"MobLizardSword");

		mAni->Create(L"Ani_LizardSword_Idle", mAtlas->GetTexture(), Vector2::Zero, Vector2(31.0f, 26.0f), 6, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_LizardSword_Move", mAtlas->GetTexture(), Vector2(0.0f, 26.0f), Vector2(31.0f, 26.0f), 8, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_LizardSword_Attack", mAtlas->GetTexture(), Vector2(0.0f, 52.0f), Vector2(31.0f, 26.0f), 9, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_LizardSword_Death", mAtlas->GetTexture(), Vector2(0.0f, 78.0f), Vector2(31.0f, 26.0f), 9, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_LizardSword_Attacked", mAtlas->GetTexture(), Vector2(0.0f, 104.0f), Vector2(31.0f, 26.0f), 7, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_LizardSword_Spawn", mAtlas->GetTexture(), Vector2(0.0f, 130.0f), Vector2(31.0f, 26.0f), 9, Vector2::Zero, 0.1f);

		mMr->Initialize();
		//mCol->SetSize(Vector2(0.5f, 0.5f));
		//mCol->SetCenter(Vector2(0.0f, 5.0f));
		AddComp<SCRIPT_MeleeMob>();
		Monster_Melee::Initialize();
	}
	void Melee_LizardSword::Update()
	{
		Monster_Melee::Update();
	}
	void Melee_LizardSword::LateUpdate()
	{
		Monster_Melee::LateUpdate();
	}
	void Melee_LizardSword::Render()
	{
		Monster_Melee::Render();
	}
}