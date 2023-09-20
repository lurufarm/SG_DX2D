#pragma once
#include "..\Engine_SOURCE\sgScript.h"

namespace sg
{
	class SCRIPT_SkelKnight : public Script
	{
	public:
		enum class eFSMState
		{
			Spwan,
			Idle,
			Move,
			Attack,
			Attacked,
			Death,
			End,
		};

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other);
		virtual void OnCollisionExit(Collider2D* other);

		void Spawn();
		void Idle();
		void Move();
		void Attack();
		void Attacked();
		void Death();

		std::wstring AnimationName(const std::wstring& animation);

		float GetDistance();
		Vector3 GetDirection();
		void SelectAttack();
		float Lerp(float a, float b, float t)
		{
			return (1 - t) * a + t * b;
		}

		bool mAttackable;

	private:
		
		eFSMState mFSMState;
		class Gobj_Monster* mOwner;
		class Gobj_Player* mTarget;
		bool mDirection;
		bool mAttacked;
		bool mDeath;

		float mTime;
		float mTime2;

		bool mLaunched;
		int mAttackNum;
		int mFireOrbNum;
		Vector3 mAttack3TargetPos;
		Vector3 mAttack3OwnerPos;
		std::wstring idle = L"Idle";
		std::wstring move = L"Move";
		std::wstring attack = L"Attack";
		std::wstring attack2 = L"Attack2";
		std::wstring attack3 = L"Attack3";
		std::wstring attack4 = L"Attack4";
		std::wstring spawn = L"Spawn";
		std::wstring death = L"Death";

		class Img_Shadow* mShadow;

	};
}
