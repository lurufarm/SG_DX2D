#pragma once
#include "..\Engine_SOURCE\sgScript.h"

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

		virtual void Update() override;

		void Idle();
		void Move(eKeyCode Key, eKeyState state, float speed);
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

	};
}
