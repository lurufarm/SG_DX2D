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
			int mHP;
			float mStrength;
			float mSpeed;
			float mRange;
			int dropEXP;
		};

		Gobj_Monster();
		~Gobj_Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		MobStat GetStat() { return mStat; }
		void SetStatHP(int hp) { mStat.mHP = hp; }


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

	};
}

