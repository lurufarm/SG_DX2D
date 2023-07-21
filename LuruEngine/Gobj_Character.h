#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgMeshRenderer.h"
#include "..\Engine_SOURCE\sgCollider2D.h"
#include "..\Engine_SOURCE\sgInput.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "SCENE_LobbyScene.h"

namespace sg
{
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


	protected:
		CharStat mStat;
		Transform* mTr;
		MeshRenderer* mMr;
		Collider2D* mCol;
	};
}

