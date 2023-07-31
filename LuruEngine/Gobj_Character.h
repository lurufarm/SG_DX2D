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
			int mLev;
			float mStrength;
			float mCoolDown;
			float mRange;
			float mSpeed;
			int mHP;
			float mExp;
		};

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		CharStat GetStat() { return mStat; }

		void SetLev(int lev) { mStat.mLev = lev; }
		void SetStrength(float strength) { mStat.mStrength = strength; }
		void SetCoolDown(float cooldown) { mStat.mCoolDown = cooldown; }
		void SetRange(float range) { mStat.mRange = range; }
		void SetSpeed(float speed) { mStat.mSpeed = speed; }
		void SetHP(int HP) { mStat.mHP = HP; }

		void SetIsPlayer(bool value) { mIsPlayer = value; }
		bool GetIsPlayer() { return mIsPlayer; }

		void SetTarget(Gobj_Monster* mob) { mTarget = mob; }
		Gobj_Monster* GetTarget() { return mTarget; }

		static void AddChar(std::wstring key, Gobj_Character* character)
		{
			mAllChars.insert(std::make_pair(key, character));
		}
		static Gobj_Character* GetChar(std::wstring key)
		{
			std::map<std::wstring, Gobj_Character*>::iterator iter = mAllChars.find(key);
			if (iter != mAllChars.end())
				return iter->second;
			else
				return nullptr;
		}
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

	private:
		static std::map<std::wstring, Gobj_Character*>mAllChars;

	};
}

