#include "SCRIPT_Player.h"

#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgAnimator.h"

#include "Gobj_Player.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	void SCRIPT_Player::Initialize()
	{
		mFSMState = ePlayerFSM::Idle;
		mOwner = (Gobj_Player*)GetOwner();
		mDirection = true;
	}

	void SCRIPT_Player::Update()
	{
		

		if (Input::KeyD(eKeyCode::A))
		{
			mKey = eKeyCode::A;
			mDirection = false;
			mKeyState = eKeyState::Down;
			mFSMState = ePlayerFSM::Move;
		}
		else if (Input::KeyP(eKeyCode::D))
		{
			mKey = eKeyCode::D;
			mDirection = true;
			mKeyState = eKeyState::Pressed;
			mFSMState = ePlayerFSM::Move;
		}
		if (Input::KeyP(eKeyCode::A))
		{
			mKey = eKeyCode::A;
			mDirection = false;
			mKeyState = eKeyState::Pressed;
			mFSMState = ePlayerFSM::Move;
		}
		else if (Input::KeyD(eKeyCode::D))
		{
			mKey = eKeyCode::D;
			mDirection = true;
			mKeyState = eKeyState::Down;
			mFSMState = ePlayerFSM::Move;
		}
		// À§¾Æ·¡
		if (Input::KeyD(eKeyCode::W))
		{
			mKey = eKeyCode::W;
			mKeyState = eKeyState::Down;
			mFSMState = ePlayerFSM::Move;
		}
		else if (Input::KeyP(eKeyCode::W))
		{
			mKey = eKeyCode::W;
			mKeyState = eKeyState::Pressed;
			mFSMState = ePlayerFSM::Move;
		}
		else if (Input::KeyD(eKeyCode::S))
		{
			mKey = eKeyCode::S;
			mKeyState = eKeyState::Down;
			mFSMState = ePlayerFSM::Move;
		}
		else if (Input::KeyP(eKeyCode::S))
		{
			mKey = eKeyCode::S;
			mKeyState = eKeyState::Pressed;
			mFSMState = ePlayerFSM::Move;
		}

		if (Input::KeyU(mKey))
		{
			isPlayed = false;
			mKeyState = eKeyState::Up;
			mFSMState = ePlayerFSM::Idle;
		}


		switch (mFSMState)
		{
		case sg::SCRIPT_Player::ePlayerFSM::Idle:
			Idle();
			break;
		case sg::SCRIPT_Player::ePlayerFSM::Move:
			Move(mKey, mKeyState, mOwner->GetStat().mSpeed);
			break;
		case sg::SCRIPT_Player::ePlayerFSM::Attack:
			Attack();
			break;
		case sg::SCRIPT_Player::ePlayerFSM::Attacked:
			Attacked();
			break;
		}

	}
	void SCRIPT_Player::Idle()
	{
		Animator* mAni = GetOwner()->GetComp<Animator>();
		std::wstring aniname = L"Ani_";
		aniname += mOwner->GetChar()->GetName();
		aniname += L"_Idle";
		if (isPlayed == false)
		{
			mAni->PlayAnimation(aniname, true, mDirection);
			isPlayed = true;
		}
		if (mKeyState == eKeyState::Down || mKeyState == eKeyState::Pressed)
		{
			mFSMState = ePlayerFSM::Move;
			isPlayed = false;
		}
	}
	void SCRIPT_Player::Move(eKeyCode key, eKeyState state, float speed)
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Animator* mAni = GetOwner()->GetComp<Animator>();
		std::wstring aniname = L"Ani_";
		aniname += mOwner->GetChar()->GetName();

		if (state == eKeyState::Down || state == eKeyState::Pressed)
		{
			aniname += L"_Move";

			if (key == eKeyCode::A)
			{
				//mDirection = false;
				pos.x -= speed * Time::DeltaTime();
				tr->SetPosition(pos);
				if (isPlayed == false)
				{
					mAni->PlayAnimation(aniname, true, mDirection);
					isPlayed = true;
				}
			}
			else if (key == eKeyCode::D)
			{
				//mDirection = true;
				pos.x += speed * Time::DeltaTime();
				tr->SetPosition(pos);
				if (isPlayed == false)
				{
					mAni->PlayAnimation(aniname, true, mDirection);
					isPlayed = true;
				}
			}
			if (key == eKeyCode::W)
			{
				pos.y += speed * Time::DeltaTime();
				tr->SetPosition(pos);
				if (isPlayed == false)
				{
					mAni->PlayAnimation(aniname, true, mDirection);
					isPlayed = true;
				}
			}
			else if (key == eKeyCode::S)
			{
				pos.y -= speed * Time::DeltaTime();
				tr->SetPosition(pos);
				if (isPlayed == false)
				{
					mAni->PlayAnimation(aniname, true, mDirection);
					isPlayed = true;
				}
			}
		}
		else
		{
			isPlayed = false;
			if (mOwner->GetEnemyNearby())
				mFSMState = ePlayerFSM::Attack;
			else
				mFSMState = ePlayerFSM::Idle;
		}

	}
	void SCRIPT_Player::Attack()
	{
		Animator* mAni = GetOwner()->GetComp<Animator>();
		std::wstring aniname = L"Ani_";
		aniname += mOwner->GetChar()->GetName();
		aniname += L"_Attack";
		if (isPlayed == false)
		{
			mAni->PlayAnimation(aniname, true, mDirection);
			isPlayed = true;
		}

		if (mOwner->GetEnemyNearby() == false)
		{
			isPlayed = false;
			mFSMState = ePlayerFSM::Idle;
		}
	}
	void SCRIPT_Player::Attacked()
	{
	}
	void SCRIPT_Player::OnCollisionEnter(Collider2D* other)
	{
	}
	void SCRIPT_Player::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_Player::OnCollisionExit(Collider2D* other)
	{
	}
}