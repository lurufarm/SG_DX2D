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
			Move2,
			Attack,
			Attacked,
			Death,
			End,
		};

		SCRIPT_Company();
		~SCRIPT_Company();

		void Initialize() override;
		void Update() override;

		void OnCollisionEnter(Collider2D* other) override;
		void OnCollisionStay(Collider2D* other) override;
		void OnCollisionExit(Collider2D* other) override;


		Vector3 RandPos(Vector3 pos);
		Vector3 RandomDirection();
		Vector3 OppositeDirection(Vector3 pos);

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
		float GetDistanceToOther()
		{
			Vector3 opos = mOtr->GetPosition();
			Vector3 tpos;
			if (mTarget)
			{
				if (mTarget->GetState() == GameObject::eState::Active)
				{
					tpos = mTarget->GetComp<Transform>()->GetPosition();
					float distance =
						(tpos - opos).Length();

					return distance;
				}
				else
				{
					IsEnemyNear = false;
					return mOwner->GetStat().mRange * 2.0f + 1.0f;
				}
			}
			else
			{
				IsEnemyNear = false;
				return mOwner->GetStat().mRange * 2.0f + 1.0f;
			}
		}
		Vector3 GetDirectionToOther(Vector3 pos)
		{
			Vector3 opos = mOtr->GetPosition();
			
			Vector3 direction = pos - opos;
			direction.Normalize();

			return direction;
		}


		GameObject* GetTarget() { return mTarget; }

	private:

		void Idle();
		void Move();
		void Move2();
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
		Vector3 mRandomDirection;

		class Transform* mOtr;
		class Transform* mPtr;
		class Animator* mOat;
		class Collider2D* mOcol;

		std::wstring idle = L"Idle";
		std::wstring move = L"Move";
		std::wstring attack = L"Attack";
		std::wstring attacked = L"Attacked";
		std::wstring death = L"Death";


	};
}
