#include "Char_Cheese.h"
#include "..\Engine_SOURCE\sgResources.h"
namespace sg
{
	Char_Cheese::Char_Cheese()
	{
		mStat.mLev = 2;
		mStat.mStrength = 15.0f;
		mStat.mCoolDown = 0.7f;
		mStat.mRange = 30.0f;
		mStat.mSpeed = 200.0f;
		mStat.mHP = 100;
		mStat.mExp = 0.0;

		SetName(L"IamCheese");
		Char_Cheese::Initialize();
	}
	Char_Cheese::~Char_Cheese()
	{
	}
	void Char_Cheese::Initialize()
	{
		//mTr = GetComp<Transform>();
		//mTr->SetPosition(0.0f, 0.0f, -1.0f);
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