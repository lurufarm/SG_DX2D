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
		
		void SetTarget(GameObject* mob) { mTarget = mob; }
		GameObject* GetTarget() { return mTarget; }
		
		void EXP(int exp)
		{
			mpStat.mExp += exp;
		}

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

		UINT nextLevelExp[4] = { 100, 130, 170, 200 };

	};
}

