#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgAnimator.h"

namespace sg
{
	class Gobj_Monster : public GameObject
	{
	public:

		struct MobStat
		{
			float mCurHP;
			float mMaxHP;
			int mStrength;
			float mDefence;
			float mSpeed;
			float mRange;
			float mCooldown;
			int dropEXP;
		};

		Gobj_Monster();
		~Gobj_Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		MobStat GetStat() { return mStat; }
		void SetStatHP(int hp) { mStat.mCurHP = hp; }

		static void AddMob(std::wstring key, Gobj_Monster* character)
		{
			mAllMobs.insert(std::make_pair(key, character));
		}
		static Gobj_Monster* GetMob(std::wstring key)
		{
			std::map<std::wstring, Gobj_Monster*>::iterator iter = mAllMobs.find(key);
			if (iter != mAllMobs.end())
				return iter->second;
			else
				return nullptr;
		}


	protected:

		MobStat mStat;
		GameObject* mPlayer;
		bool mTargeted;

		Transform* mTr;
		MeshRenderer* mMr;
		Collider2D* mCol;
		class Animator* mAni;
		std::shared_ptr<Material> mAtlas;

	private:
		static std::map<std::wstring, Gobj_Monster*>mAllMobs;

	};
}

