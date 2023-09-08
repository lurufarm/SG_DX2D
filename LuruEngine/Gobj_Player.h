#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgAnimator.h"
#include "..\Engine_SOURCE\sgLight.h"
#include "Gobj_Character.h"
#include "Gobj_Monster.h"
#include "SCRIPT_CameraScript.h"

namespace sg
{
	class Gobj_Player : public GameObject
	{
	public:
		Gobj_Player();
		~Gobj_Player();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void Initialize2();

		static void SetChar(Gobj_Character* character)
		{
			if (mpChar != nullptr)
				mpChar->SetIsPlayer(false);
			mpChar = character;
			std::map<std::wstring, Animation*> charAnis = mpChar->GetComp<Animator>()->GetAnimations();
			mAni->SetAnimations(charAnis);
			mpStat = mpChar->GetStat();			
			GetChar()->SetIsPlayer(true);
			mAni->PlayAnimation(mAni->GetAnimations().begin()->second->GetKey(), true, true);
		}
		static Gobj_Character* GetChar() { return mpChar; }

		static void SetEnemyNearby(bool value) { mEnemyNearby = value; }
		static bool GetEnemyNearby() { return mEnemyNearby; }

		void SetStat(Gobj_Character::CharStat stat) { mpStat = stat; }
		Gobj_Character::CharStat GetStat() { return mpStat; }
		
		void BonusLife() { mpStat.mLife = 1; }
		void Heal(float value) { mpStat.mCurHP += mpStat.mMaxHP * mpStat.mHPHealRatio * value; }
		void HPSteal() { mpStat.mCurHP += mpStat.mStrength * mpStat.mHPStealRatio; }
		void EnhenceHPHealRatio() { mpStat.mHPHealRatio += 0.05f; }
		void EnhenceHPStealRatio() { mpStat.mHPStealRatio += 0.02f; }
		void EnhenceMaxHP()
		{
			float addhp = mpStat.mMaxHP += mpStat.mMaxHP * 0.1f;
			mpStat.mMaxHP += addhp;
			mpStat.mCurHP += addhp;
		}
		
		void EnhenceStrength() { mpStat.mStrength += mpStat.mStrength * 0.15f; }
		void EnhenceDefence() { mpStat.mDefence += 0.1f; }
		void EnhenceAttackSpeed() { mpStat.mAttackSpeed -= 0.05f; }
		void EnhenceAttackDuration() 
		{ 
			if (mpStat.mAttackDuration != 0.0f)
				mpStat.mAttackDuration += 0.3f;
		}
		void EnhenceAttackCount()
		{
			if (mpStat.mAttackCount < 3)
				mpStat.mAttackCount++;
		}
		void EnhenceRange() { mpStat.mRange += mpStat.mRange * 0.05f; }
		void EnhenceProjectileCount() 
		{
			if (mpStat.mProjectileCount < 5)
				mpStat.mProjectileCount++;
			mpStat.mDamageScaling = 0.75f;
		}
		void EnhenceSpeed() { mpStat.mSpeed += mpStat.mSpeed *= 0.1f; }		
		void EXP(int exp)
		{
			mpStat.mExp += exp;
		}


		void SetTarget(GameObject* mob) { mTarget = mob; }
		GameObject* GetTarget() { return mTarget; }
		

	private:
		void LevelUp();

		static Transform* mTr;
		static MeshRenderer* mMr;
		static Collider2D* mCol;
		static Animator* mAni;
		static Light* mLg;

		static Gobj_Character* mpChar;
		static Gobj_Character::CharStat mpStat;
		static std::vector<Gobj_Character*> mCompanies;
		static bool mEnemyNearby;

		GameObject* mTarget;

		UINT nextLevelExp[4] = { 200, 250, 300, 400 };

	};
}

