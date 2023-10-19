#include "Char_Robo.h"

namespace sg
{
	Char_Robo::Char_Robo()
	{
		mStat.mLev = 1;
		mStat.mLife = 0;
		mStat.mStrength = 19.0f;
		mStat.mDefence = 0.0f;
		mStat.mCooldown = 2.0f;
		mStat.mRange = 100.0f;
		mStat.mSpeed = 60.0f;
		mStat.mAttackSpeed = 50.0f;
		mStat.mAttackDuration = 0.0f;
		mStat.mAttackCount = 0.0f;
		mStat.mCurHP = 90;
		mStat.mMaxHP = 90;
		mStat.mHPHealRatio = 0.05f;
		mStat.mHPStealRatio = 0.0f;
		mStat.mProjectileCount = 0;
		mStat.mDamageScaling = 1.0f;
		mStat.mExp = 0.0;

		SetName(L"Robo");
		Char_Robo::Initialize();
	}
	Char_Robo::~Char_Robo()
	{
	}
	void Char_Robo::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMr->SetMaterial(Resources::Find<Material>(L"AnimationMaterial"));
		mAni = GetComp<Animator>();
		mAtlas = Resources::Load<Texture>(L"Ani_Robo", L"..\\Resources\\Character\\Robo\\Robo.png");
		mAni->Create(L"Ani_Robo_Idle", mAtlas, Vector2(0.0f, 0.0f), Vector2(22.0f, 19.0f), 7, Vector2::Zero, 0.08f);
		mAni->Create(L"Ani_Robo_Move", mAtlas, Vector2(0.0f, 19.0f), Vector2(22.0f, 19.0f), 8, Vector2::Zero, 0.08f);
		mAni->Create(L"Ani_Robo_Death", mAtlas, Vector2(0.0f, 38.0f), Vector2(22.0f, 19.0f), 18, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Robo_Attack", mAtlas, Vector2(0.0f, 57.0f), Vector2(22.0f, 19.0f), 15, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Robo_Attacked", mAtlas, Vector2(0.0f, 76.0f), Vector2(22.0f, 19.0f), 7, Vector2::Zero, 0.05f);
		mMr->Initialize();

		Gobj_Character::Initialize();
	}
	void Char_Robo::Update()
	{
		Gobj_Character::Update();
	}
	void Char_Robo::LateUpdate()
	{
		Gobj_Character::LateUpdate();
	}
	void Char_Robo::Render()
	{
		Gobj_Character::Render();
	}
}