#include "Gobj_Character.h"
#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Gobj_Player.h"
#include "Img_LevUP.h"
#include "Img_LevUP2.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	Gobj_Character::Gobj_Character()
	{
		AddComp<MeshRenderer>();
		AddComp<Animator>();
		mIsPlayer = false;
	}
	Gobj_Character::~Gobj_Character()
	{
	}
	void Gobj_Character::Initialize()
	{
		SceneManager::AddChar(this->GetName(), this);
	}
	void Gobj_Character::Update()
	{
		if (mStat.mLev < 5 && mStat.mExp >= nextLevelExp[mStat.mLev - 1])
		{
			LevelUp();
		}

		GameObject::Update();
	}
	void Gobj_Character::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Gobj_Character::Render()
	{
		GameObject::Render();
	}

	void Gobj_Character::LevelUp()
	{
		Vector3 pos0 = mTr->GetPosition();
		pos0.y += 10.0f;
		object::Instantiate<Img_LevUP>(pos0, eLayerType::UI, SceneManager::GetActiveScene());
		object::Instantiate<Img_LevUP2>(eLayerType::Effect, SceneManager::GetActiveScene());

		mStat.mLev++;
		if (mStat.mStrength > 25)
			mStat.mStrength += mStat.mStrength * 0.25f;
		else if (mStat.mStrength < 25)
			mStat.mStrength += mStat.mStrength * 0.1f;
		mStat.mDefence += mStat.mDefence * 0.1f;
		mStat.mCooldown -= mStat.mCooldown * 0.1f;
		mStat.mRange += mStat.mRange * 0.05f;
		mStat.mSpeed += mStat.mSpeed * 0.05f;
		mStat.mAttackSpeed -= mStat.mAttackSpeed * 0.05f;
		if (mStat.mAttackDuration != 0)
			mStat.mAttackDuration += 0.3f;
		mStat.mMaxHP += mStat.mMaxHP * 0.1f;
		mStat.mCurHP += mStat.mMaxHP * 0.1f;
		if (mStat.mLev % 2 == 1)
		{
			if (mStat.mProjectileCount > 0)
			{
				mStat.mProjectileCount++;
				mStat.mDamageScaling = 0.75f;
			}
		}
		mStat.mExp -= nextLevelExp[mStat.mLev - 2];
	}

}