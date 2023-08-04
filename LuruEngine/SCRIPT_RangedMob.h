#pragma once
#include "..\Engine_SOURCE\sgScript.h"

namespace sg
{
	class SCRIPT_RangedMob : public Script
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

		SCRIPT_RangedMob();
		~SCRIPT_RangedMob();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

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

	private:

		eFSMState mFSMState;
		class Gobj_Monster* mOwner;
		class Gobj_Player* mTarget;
		bool mDirection;
		bool mAttacked;
		bool mDeath;
		float mTime;

		std::wstring idle = L"Idle";
		std::wstring move = L"Move";
		std::wstring attack = L"Attack";
		std::wstring spawn = L"Spawn";
		std::wstring attacked = L"Attacked";
		std::wstring death = L"Death";

	};
}