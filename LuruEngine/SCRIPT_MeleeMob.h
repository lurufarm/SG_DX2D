#pragma once
#include "..\Engine_SOURCE\sgScript.h"

namespace sg
{
	class SCRIPT_MeleeMob : public Script
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

		SCRIPT_MeleeMob();
		~SCRIPT_MeleeMob();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		virtual void Spawn();
		virtual void Idle();
		virtual void Move();
		virtual void Attack();
		virtual void Attacked();
		virtual void Death();

		std::wstring AnimationName(const std::wstring& animation);

		float GetDistance();
		Vector3 GetDirection();
		eFSMState GetMeleeState() { return mFSMState; }

		bool mAttackable;


	protected:
		bool mDirection;
		bool mAttacked;
		eFSMState mFSMState;
		class Gobj_Monster* mOwner;
		class Gobj_Player* mTarget;
		bool mDeath;
		float mTime;

		Vector2 mColSize;

		std::wstring idle = L"Idle";
		std::wstring move = L"Move";
		std::wstring attack = L"Attack";
		std::wstring spawn = L"Spawn";
		std::wstring attacked = L"Attacked";
		std::wstring death = L"Death";

	};
}