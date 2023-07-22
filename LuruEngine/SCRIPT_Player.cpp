#include "SCRIPT_Player.h"

#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgTransform.h"

#include "Gobj_Player.h"

namespace sg
{

	void SCRIPT_Player::Update()
	{
		mOwner = dynamic_cast<Gobj_Player*>(GetOwner());

		if (Input::KeyD(eKeyCode::A))
		{
			mKey = eKeyCode::A;
			mFSMState = ePlayerFSM::Move;
		}
		else if (Input::KeyD(eKeyCode::D))
		{
			mKey = eKeyCode::D;
			mFSMState = ePlayerFSM::Move;
		}
		if (Input::KeyD(eKeyCode::W))
		{
			mKey = eKeyCode::W;
			mFSMState = ePlayerFSM::Move;
		}
		else if (Input::KeyD(eKeyCode::S))
		{
			mKey = eKeyCode::S;
			mFSMState = ePlayerFSM::Move;
		}
		if (Input::KeyU(mKey))
		{
			mFSMState = ePlayerFSM::Idle;
		}


		switch (mFSMState)
		{
		case sg::SCRIPT_Player::ePlayerFSM::Idle:
			Idle();
			break;
		case sg::SCRIPT_Player::ePlayerFSM::Move:
			Move(mKey, mKeyState, mOwner->GetChar()->GetStat().mSpeed);
			break;
		case sg::SCRIPT_Player::ePlayerFSM::Attack:
			Attack();
			break;
		case sg::SCRIPT_Player::ePlayerFSM::Attacked:
			Attacked();
			break;
		default:
			break;
		}

	}
	void SCRIPT_Player::Idle()
	{
	}
	void SCRIPT_Player::Move(eKeyCode key, eKeyState state, float speed)
	{
		Transform* tr = GetOwner()->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();

		if (state == eKeyState::Down || state == eKeyState::Pressed)
		{
			if (key == eKeyCode::A)
			{
				pos.x -= speed * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (key == eKeyCode::D)
			{
				pos.x += speed * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			if (key == eKeyCode::W)
			{
				pos.y += speed * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else if (key == eKeyCode::S)
			{
				pos.y -= speed * Time::DeltaTime();
				tr->SetPosition(pos);
			}
		}
		else
		{
			if (mOwner->GetEnemyNearby())
				mFSMState = ePlayerFSM::Attack;
			else
				mFSMState = ePlayerFSM::Idle;

		}

	}
	void SCRIPT_Player::Attack()
	{

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