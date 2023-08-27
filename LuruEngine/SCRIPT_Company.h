#pragma once
#include "..\Engine_SOURCE\sgScript.h"
#include "SCRIPT_Player.h"

namespace sg
{
	class SCRIPT_Company : public Script
	{
	public:
		enum class eCompanyFSM
		{
			Idle,
			Move,
			Attack,
			Attacked,
			Death,
			End,
		};

		SCRIPT_Company();
		~SCRIPT_Company();

		void Initialize();
		void Update();

		Vector3 RandPos(Vector3 pos);
		std::wstring AnimationName(const std::wstring& animation);
		float GetDistanceToPlayer()
		{
			Vector3 opos = mOtr->GetPosition();
			Vector3 ppos = mPtr->GetPosition();
			
			float distance =
				(ppos - opos).Length();

			return distance;
		}
		Vector3 GetDirectionToPlayer()
		{
			Vector3 opos = mOtr->GetPosition();
			Vector3 ppos = mPtr->GetPosition();

			Vector3 direction = ppos - opos;
			direction.Normalize();

			return direction;
		}

		GameObject* GetTarget() { return mTarget; }

	private:

		void Idle();
		void Move();
		void Attack();
		void Death();

		class Gobj_Player* mPlayer;
		class Gobj_Character* mOwner;
		class GameObject* mTarget;

		eCompanyFSM mFSMState;
		
		bool mDirection;
		bool mAttacked = false;
		bool mDeath = false;
		bool IsEnemyNear;

		float mTime;

		class Transform* mOtr;
		class Transform* mPtr;
		class Animator* mOat;

		std::wstring idle = L"Idle";
		std::wstring move = L"Move";
		std::wstring attack = L"Attack";
		std::wstring attacked = L"Attacked";
		std::wstring death = L"Death";


	};
}
