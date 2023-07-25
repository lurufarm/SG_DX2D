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
		void Move(Input::Key key, float speed);
		void Attack();
		void Attacked();
		
		std::wstring AnimationName(const std::wstring& animation)
		{
			std::wstring animationName = L"Ani_";
			animationName += mOwner->GetChar()->GetName();
			animationName += L"_";
			animationName += animation;
			return animationName;
		}

		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other);
		virtual void OnCollisionExit(Collider2D* other);
	private:
		ePlayerFSM mFSMState;
		Input::Key mKey;
		class Gobj_Player* mOwner;

		std::wstring mAniname;
		bool mDirection;
		bool isPlayed = false;

		float mTime;
		
		std::wstring idle = L"Idle";
		std::wstring move = L"Move";
		std::wstring attack = L"Attack";

	};
}
