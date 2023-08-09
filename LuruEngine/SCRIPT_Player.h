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
		virtual void Initialize() override;
		virtual void Update() override;

		void Idle();
		void Move(Input::Key key, float speed);
		void Attack();
		void Attacked();
		void Death();
		

		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other);
		virtual void OnCollisionExit(Collider2D* other);

		std::wstring AnimationName(const std::wstring& animation);
	private:
		ePlayerFSM mFSMState;
		Input::Key mKey;
		class Gobj_Player* mOwner;

		std::wstring mAniname;
		bool mDirection;
		bool mAttacked = false;
		bool mDeath = false;

		float mTime;
		
		std::wstring idle = L"Idle";
		std::wstring move = L"Move";
		std::wstring attack = L"Attack";
		std::wstring attacked = L"Attacked";
		std::wstring death = L"Death";

	};
}
