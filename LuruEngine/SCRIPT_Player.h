#pragma once
#include "..\Engine_SOURCE\sgScript.h"
#include "..\Engine_SOURCE\sgTime.h"
#include "..\Engine_SOURCE\sgInput.h"

namespace sg
{
	class SCRIPT_Player : public Script
	{

	public:
		enum class ePlayerFSM
		{
			Idle,
			Move,
			Attack,
			Attacked,
			Death,
			End,
		};
		void Initialize() override;
		void Update() override;


		template <typename Monster>
		Vector3 GetAttackedDir(Monster* mob)
		{
			GameObject* obj = dynamic_cast<GameObject*>(mob);
			Vector3 dir3 = obj->GetComp<Transform>()->GetPosition();
			Vector3 mypos = mOwner->GetComp<Transform>()->GetPosition();
			mypos -= dir3;
			mypos.Normalize();
			return mypos;
		}

		void OnCollisionEnter(Collider2D* other) override;
		void OnCollisionStay(Collider2D* other) override;
		void OnCollisionExit(Collider2D* other) override;


		std::wstring AnimationName(const std::wstring& animation);
		ePlayerFSM GetState() { return mFSMState; }
		float GetDistanceToEnemy()
		{
			Vector3 opos = mOwner->GetComp<Transform>()->GetPosition();
			Vector3 tpos;
			if (mOwner->GetTarget())
			{
				if (mOwner->GetTarget()->GetState() == GameObject::eState::Active)
				{
					tpos = mOwner->GetTarget()->GetComp<Transform>()->GetPosition();
					float distance =
						(tpos - opos).Length();

					return distance;
				}
				else
				{
					mOwner->SetEnemyNearby(false);
					return mOwner->GetStat().mRange * 2.0f + 1.0f;
				}
			}
			else
			{
				mOwner->SetEnemyNearby(false);
				return mOwner->GetStat().mRange * 2.0f + 1.0f;
			}
		}
		void DeductPlayerHP(Gobj_Character::CharStat& pStat, float damage);
		void DeductPlayerHP(Gobj_Character::CharStat& pStat, GameObject* attacker);
	private:

		void Idle();
		void Move(Input::Key key, float speed);
		void Attack();
		void Attacked();
		void Death();

		ePlayerFSM mFSMState;
		Input::Key mKey;
		class Gobj_Player* mOwner;

		bool mDirection;
		bool mAttacked = false;
		bool mDeath = false;

		Vector3 mAttackedDir;

		float mTime;
		float mAttackedTime;
		
		std::wstring idle = L"Idle";
		std::wstring move = L"Move";
		std::wstring attack = L"Attack";
		std::wstring attacked = L"Attacked";
		std::wstring death = L"Death";

	};
}
