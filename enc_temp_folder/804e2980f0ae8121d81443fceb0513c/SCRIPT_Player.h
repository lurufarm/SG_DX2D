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
		};
		virtual void Initialize() override;
		virtual void Update() override;

		void Idle();
		void Move(eKeyCode key, eKeyState state, float speed);
		void Attack();
		void Attacked();
		
		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other);
		virtual void OnCollisionExit(Collider2D* other);
	private:
		ePlayerFSM mFSMState;
		eKeyCode mKey;
		eKeyState mKeyState;
		class Gobj_Player* mOwner;

		std::wstring mAniname;
		bool mDirection;
		bool isPlayed = false;
	};
}
