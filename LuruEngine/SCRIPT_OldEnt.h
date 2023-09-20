#pragma once
#include "..\Engine_SOURCE\sgScript.h"

namespace sg
{
	class SCRIPT_OldEnt : public Script
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

		SCRIPT_OldEnt();
		~SCRIPT_OldEnt();

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
		Vector3 StemPos(Vector3 pos);

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
		bool mAttackNum;

		std::wstring idle = L"Idle";
		std::wstring move = L"Move";
		std::wstring attack = L"Attack";
		std::wstring attack2 = L"Attack2";
		std::wstring spawn = L"Spawn";
		std::wstring attacked = L"Attacked";
		std::wstring death = L"Death";

	};
}