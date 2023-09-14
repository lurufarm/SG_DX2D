#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgMeshRenderer.h"
#include "..\Engine_SOURCE\sgCollider2D.h"
#include "..\Engine_SOURCE\sgAnimator.h"

namespace sg
{
	class Gobj_Monster;
	class Gobj_Character : public GameObject
	{
	public:
		Gobj_Character();
		~Gobj_Character();

		struct CharStat
		{
			int mLev = 1;
			int mLife = 0;
			float mStrength;
			float mDefence = 0;
			float mCooldown;
			float mRange;
			float mSpeed;
			float mAttackSpeed = 1;
			float mAttackDuration = 0;
			int mAttackCount;
			float mCurHP;
			float mMaxHP;
			float mHPStealRatio = 0.0f;
			float mHPHealRatio = 0.05;
			int mProjectileCount;
			float mDamageScaling;
			float mExp;
		};

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetStat(CharStat stat) { mStat = stat; }
		CharStat GetStat() { return mStat; }



		void SetIsPlayer(bool value) { mIsPlayer = value; }
		bool GetIsPlayer() { return mIsPlayer; }

		void SetTarget(Gobj_Monster* mob) { mTarget = mob; }
		Gobj_Monster* GetTarget() { return mTarget; }

		std::shared_ptr<Texture> GetAtlas() {return mAtlas;}

		void BonusLife() { mStat.mLife = 1; }
		void Heal(float value) { mStat.mCurHP += mStat.mMaxHP * mStat.mHPHealRatio * value; }
		void HPSteal() { mStat.mCurHP += mStat.mStrength * mStat.mHPStealRatio; }
		void EnhenceHPHealRatio() { mStat.mHPHealRatio += 0.05f; }
		void EnhenceHPStealRatio() { mStat.mHPStealRatio += 0.02f; }
		void EnhenceMaxHP()
		{
			float addhp = mStat.mMaxHP += mStat.mMaxHP * 0.1f;
			mStat.mMaxHP += addhp;
			mStat.mCurHP += addhp;
		}

		void EnhenceStrength() { mStat.mStrength += mStat.mStrength * 0.15f; }
		void EnhenceDefence() { mStat.mDefence += 0.1f; }
		void EnhenceAttackSpeed() { mStat.mAttackSpeed -= 0.05f; }
		void EnhenceAttackDuration()
		{
			if (mStat.mAttackDuration != 0.0f)
				mStat.mAttackDuration += 0.3f;
		}
		void EnhenceAttackCount()
		{
			if (mStat.mAttackCount < 3 && mStat.mAttackCount > 0)
				mStat.mAttackCount++;
		}
		void EnhenceRange() { mStat.mRange += mStat.mRange * 0.05f; }
		void EnhenceProjectileCount()
		{
			if (mStat.mProjectileCount < 5 && mStat.mProjectileCount > 0)
			{
				mStat.mProjectileCount++;
				mStat.mDamageScaling = 0.75f;
			}
		}
		void EnhenceSpeed() { mStat.mSpeed += mStat.mSpeed *= 0.1f; }
		void EXP(int exp)
		{
			mStat.mExp += exp;
		}

		void LevelUp();

	protected:
		CharStat mStat;
		Transform* mTr;
		MeshRenderer* mMr;
		Animator* mAni;
		bool mIsPlayer;
		Gobj_Monster* mTarget;

		std::shared_ptr<Texture> mAtlas;
		class Gobj_Bullet* mMyBullet;

		UINT nextLevelExp[4] = { 200, 250, 300, 400 };


	private:
		static std::map<std::wstring, Gobj_Character*>mAllChars;

	};
}

