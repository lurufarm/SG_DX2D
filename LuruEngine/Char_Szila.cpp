#include "Char_Szila.h"

namespace sg
{
	Char_Szila::Char_Szila()
	{
		mStat.mLev = 1;
		mStat.mLife = 0;
		mStat.mStrength = 19.0f;
		mStat.mDefence = 0.0f;
		mStat.mCooldown = 2.0f;
		mStat.mRange = 100.0f;
		mStat.mSpeed = 40.0f;
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

		SetName(L"Szila");
		Char_Szila::Initialize();
	}
	Char_Szila::~Char_Szila()
	{
	}
	void Char_Szila::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMr->SetMaterial(Resources::Find<Material>(L"AnimationMaterial"));
		mAni = GetComp<Animator>();
		mAtlas = Resources::Load<Texture>(L"Ani_Szila", L"..\\Resources\\Character\\Szila\\szila.png");
		mAni->Create(L"Ani_Szila_Idle", mAtlas, Vector2(0.0f, 19.0f), Vector2(22.0f, 19.0f), 6, Vector2::Zero, 0.08f);
		mAni->Create(L"Ani_Szila_Move", mAtlas, Vector2::Zero, Vector2(22.0f, 19.0f), 8, Vector2::Zero, 0.08f);
		mAni->Create(L"Ani_Szila_Death", mAtlas, Vector2(0.0f, 38.0f), Vector2(22.0f, 19.0f), 19, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Szila_Attack", mAtlas, Vector2(0.0f, 57.0f), Vector2(22.0f, 19.0f), 6, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Szila_Attacked", mAtlas, Vector2(0.0f, 76.0f), Vector2(22.0f, 19.0f), 8, Vector2::Zero, 0.05f);
		mMr->Initialize();

		Gobj_Character::Initialize();
	}
	void Char_Szila::Update()
	{
		Gobj_Character::Update();
	}
	void Char_Szila::LateUpdate()
	{
		Gobj_Character::LateUpdate();
	}
	void Char_Szila::Render()
	{
		Gobj_Character::Render();
	}
}