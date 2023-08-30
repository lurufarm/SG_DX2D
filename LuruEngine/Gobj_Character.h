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

		CharStat GetStat() { return mStat; }

		//void SetLev(int lev) { mStat.mLev = lev; }
		//void SetStrength(float strength) { mStat.mStrength = strength; }
		//void SetCoolDown(float cooldown) { mStat.mCooldown = cooldown; }
		//void SetRange(float range) { mStat.mRange = range; }
		//void SetSpeed(float speed) { mStat.mSpeed = speed; }
		//void SetAttackSpeed(float attackspeed) { mStat.mAttackSpeed = attackspeed; }
		//void SetHP(int HP) { mStat.mCurHP = HP; }


		void SetIsPlayer(bool value) { mIsPlayer = value; }
		bool GetIsPlayer() { return mIsPlayer; }

		void SetTarget(Gobj_Monster* mob) { mTarget = mob; }
		Gobj_Monster* GetTarget() { return mTarget; }

		std::shared_ptr<Texture> GetAtlas() {return mAtlas;}


	protected:
		CharStat mStat;
		Transform* mTr;
		MeshRenderer* mMr;
		Animator* mAni;
		bool mIsPlayer;
		Gobj_Monster* mTarget;

		std::shared_ptr<Texture> mAtlas;
		class Gobj_Bullet* mMyBullet;

		UINT NeedEXP[4] = { 100, 150, 200, 250 };


	private:
		static std::map<std::wstring, Gobj_Character*>mAllChars;

	};
}

