#include "Char_Lucy.h"

namespace sg
{
	Char_Lucy::Char_Lucy()
	{
		mStat.mLev = 1;
		mStat.mLife = 0;
		mStat.mStrength = 36.0f;
		mStat.mDefence = 0.0f;
		mStat.mCooldown = 1.7f;
		mStat.mRange = 50.0f;
		mStat.mSpeed = 40.0f;
		mStat.mAttackSpeed = 50.0f;
		mStat.mAttackDuration = 0.0f;
		mStat.mAttackCount = 1;
		mStat.mCurHP = 90;
		mStat.mMaxHP = 90;
		mStat.mHPHealRatio = 0.05f;
		mStat.mHPStealRatio = 0.0f;
		mStat.mProjectileCount = 1;
		mStat.mDamageScaling = 1.0f;
		mStat.mExp = 0.0;

		SetName(L"Lucy");
		Char_Lucy::Initialize();

	}
	Char_Lucy::~Char_Lucy()
	{

	}
	void Char_Lucy::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMr->SetMaterial(Resources::Find<Material>(L"AnimationMaterial"));
		mAni = GetComp<Animator>();
		mAtlas = Resources::Load<Texture>(L"Ani_Lucy", L"..\\Resources\\Character\\Lucy\\Lucy.png");
		mAni->Create(L"Ani_Lucy_Idle", mAtlas, Vector2(0.0f, 0.0f), Vector2(22.0f, 21.0f), 7, Vector2::Zero, 0.08f);
		mAni->Create(L"Ani_Lucy_Move", mAtlas, Vector2(0.0f, 21.0f), Vector2(22.0f, 21.0f), 9, Vector2::Zero, 0.08f);
		mAni->Create(L"Ani_Lucy_Attack", mAtlas, Vector2(0.0f, 42.0f), Vector2(22.0f, 21.0f), 10, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Lucy_Death", mAtlas, Vector2(0.0f, 63.0f), Vector2(22.0f, 21.0f), 18, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Lucy_Attacked", mAtlas, Vector2(0.0f, 84.0f), Vector2(22.0f, 21.0f), 7, Vector2::Zero, 0.05f);
		mMr->Initialize();

		Gobj_Character::Initialize();
	}
	void Char_Lucy::Update()
	{
		Gobj_Character::Update();
	}
	void Char_Lucy::LateUpdate()
	{
		Gobj_Character::LateUpdate();
	}
	void Char_Lucy::Render()
	{
		Gobj_Character::Render();
	}
}