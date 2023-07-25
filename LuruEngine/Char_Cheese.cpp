#include "Char_Cheese.h"
#include "..\Engine_SOURCE\sgResources.h"
namespace sg
{
	Char_Cheese::Char_Cheese()
	{
		mStat.mLev = 2;
		mStat.mStrength = 15.0f;
		mStat.mCoolDown = 0.7f;
		mStat.mRange = 100.0f;
		mStat.mSpeed = 50.0f;
		mStat.mHP = 100;
		mStat.mExp = 0.0;

		SetName(L"Cheese");
		Char_Cheese::Initialize();
	}
	Char_Cheese::~Char_Cheese()
	{
	}
	void Char_Cheese::Initialize()
	{
		mMr = GetComp<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMr->SetMaterial(Resources::Find<Material>(L"AnimationMaterial"));
		//mMr->Initialize();
		mAni = GetComp<Animator>();
		mAtlas = Resources::Load<Texture>(L"Ani_Cheese", L"..\\Resources\\Character\\Cheese\\cheese.png");
		mAni->Create(L"Ani_Cheese_Idle", mAtlas, Vector2(0.0f, 20.0f), Vector2(24.0f, 20.0f), 9, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Cheese_Move", mAtlas, Vector2(0.0f, 0.0f), Vector2(24.0f, 20.0f), 8, Vector2::Zero, 0.05f);
		mAni->Create(L"Ani_Cheese_Attack", mAtlas, Vector2(0.0f, 40.0f), Vector2(24.0f, 20.0f), 4, Vector2::Zero, 0.1f);
		mAni->Create(L"Ani_Cheese_Death", mAtlas, Vector2(0.0f, 60.0f), Vector2(24.0f, 20.0f), 18, Vector2::Zero, 0.05f);
	}
	void Char_Cheese::Update()
	{
		Gobj_Character::Update();
	}
	void Char_Cheese::LateUpdate()
	{
		Gobj_Character::LateUpdate();
	}
	void Char_Cheese::Render()
	{
		Gobj_Character::Render();
	}
}