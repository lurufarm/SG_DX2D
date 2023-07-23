#include "SCRIPT_Player.h"

#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgAnimator.h"

#include "Gobj_Player.h"
#include "Bullet_CheeseArrow.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	void SCRIPT_Player::Initialize()
	{
		mFSMState = ePlayerFSM::Idle;
		mOwner = (Gobj_Player*)GetOwner();
		mDirection = true;
		isPlayed = false;
		mTime = 0.0f;
	}

	void SCRIPT_Player::Update()
	{
		mTime += Time::DeltaTime();

		switch (mFSMState)
		{
		case sg::SCRIPT_Player::ePlayerFSM::Idle:
			Idle();
			break;
		case sg::SCRIPT_Player::ePlayerFSM::Move:
			Move(mKey, mOwner->GetStat().mSpeed);
			break;
		case sg::SCRIPT_Player::ePlayerFSM::Attack:
			Attack();
			break;
		case sg::SCRIPT_Player::ePlayerFSM::Attacked:
			Attacked();
			break;
		}

		if (Input::GetAnyKey())
		{
			mKey = Input::GetAnyKeyInfo();
			mFSMState = ePlayerFSM::Move;
		}
		else
		{
			if (mOwner->GetEnemyNearby())
				mFSMState = ePlayerFSM::Attack;
			else
				mFSMState = ePlayerFSM::Idle;
		}

		std::vector<GameObject*> monsters = SceneManager::GetActiveScene()->GetLayer(eLayerType::Monster).GetGameObjects();
		std::map<float, GameObject*> distanceOfMob;
		Transform* tr = mOwner->GetComp<Transform>();
		Vector3 ownerpos = tr->GetPosition();
		if (monsters.size() > 0)
		{
			for (GameObject* mob : monsters)
			{
				Vector3 mobpos = mob->GetComp<Transform>()->GetPosition();

				float distance = sqrt(pow(mobpos.x - ownerpos.x, 2)
					+ pow(mobpos.y - ownerpos.y, 2));

				distanceOfMob.insert(std::make_pair(distance, mob));
			}
			
			mOwner->SetTarget(distanceOfMob.begin()->second);
			if (distanceOfMob.begin()->first <= mOwner->GetChar()->GetStat().mRange)
			{
				mOwner->SetEnemyNearby(true);
				if (mOwner->GetTarget()->GetComp<Transform>()->GetPosition().x > ownerpos.x)
				{
					mDirection = true;
				}
				else
				{
					mDirection = false;
				}
			}
			else
			{
				mOwner->SetEnemyNearby(false);
			}

		}
		else if (SceneManager::GetActiveScene()->GetLayer(eLayerType::Monster).GetGameObjects().size() == 0)
		{
			mOwner->SetEnemyNearby(false);
		}

	};

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
		if (Input::GetAnyKey())
		{
			isPlayed = false;
			mFSMState = ePlayerFSM::Move;
		}
	}
	void SCRIPT_Player::Move(Input::Key key, float speed)
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Animator* mAni = GetOwner()->GetComp<Animator>();
		std::wstring aniname = L"Ani_";
		aniname += mOwner->GetChar()->GetName();

		if (Input::GetAnyKey())
		{
			aniname += L"_Move";
			mKey = Input::GetAnyKeyInfo();

			if (Input::GetAnyKeyInfo().state == eKeyState::Down)
			{
				isPlayed = false;
			}

			if (mKey.key == eKeyCode::A 
				&& Input::GetKeyState(eKeyCode::W) == eKeyState::None 
				&& Input::GetKeyState(eKeyCode::S) == eKeyState::None)
			{
				mDirection = false;
				pos.x -= speed * Time::DeltaTime();
				tr->SetPosition(pos);
				if (isPlayed == false)
				{
					mAni->PlayAnimation(aniname, true, mDirection);
					isPlayed = true;
				}
			}
			else if (mKey.key == eKeyCode::D 
				&& Input::GetKeyState(eKeyCode::W) == eKeyState::None 
				&& Input::GetKeyState(eKeyCode::S) == eKeyState::None)
			{
				mDirection = true;
				pos.x += speed * Time::DeltaTime();
				tr->SetPosition(pos);
				if (isPlayed == false)
				{
					mAni->PlayAnimation(aniname, true, mDirection);
					isPlayed = true;
				}
			}
			else if (mKey.key == eKeyCode::W 
				&& Input::GetKeyState(eKeyCode::A) == eKeyState::None 
				&& Input::GetKeyState(eKeyCode::D) == eKeyState::None)
			{
				pos.y += speed * Time::DeltaTime();
				tr->SetPosition(pos);
				if (isPlayed == false)
				{
					mAni->PlayAnimation(aniname, true, mDirection);
					isPlayed = true;
				}
			}
			else if (mKey.key == eKeyCode::S 
				&& Input::GetKeyState(eKeyCode::A) == eKeyState::None 
				&& Input::GetKeyState(eKeyCode::D) == eKeyState::None)
			{
				pos.y -= speed * Time::DeltaTime();
				tr->SetPosition(pos);
				if (isPlayed == false)
				{
					mAni->PlayAnimation(aniname, true, mDirection);
					isPlayed = true;
				}
			}
			
			if (Input::KeyP(eKeyCode::A) 
				&& Input::KeyP(eKeyCode::W))
			{
				mDirection = false;
				pos.x -= (speed / 1.5f) * Time::DeltaTime();
				pos.y += (speed / 1.5f) * Time::DeltaTime();
				tr->SetPosition(pos);
				if (isPlayed == false)
				{
					mAni->PlayAnimation(aniname, true, mDirection);
					isPlayed = true;
				}
			}
			else if (Input::KeyP(eKeyCode::A) 
				&& Input::KeyP(eKeyCode::S))
			{
				mDirection = false;
				pos.x -= (speed / 1.5f) * Time::DeltaTime();
				pos.y -= (speed / 1.5f) * Time::DeltaTime();
				tr->SetPosition(pos);
				if (isPlayed == false)
				{
					mAni->PlayAnimation(aniname, true, mDirection);
					isPlayed = true;
				}
			}
			else if (Input::KeyP(eKeyCode::D) 
				&& Input::KeyP(eKeyCode::W))
			{
				mDirection = true;
				pos.x += (speed / 1.5f) * Time::DeltaTime();
				pos.y += (speed / 1.5f) * Time::DeltaTime();
				tr->SetPosition(pos);
				if (isPlayed == false)
				{
					mAni->PlayAnimation(aniname, true, mDirection);
					isPlayed = true;
				}
			}
			else if (Input::KeyP(eKeyCode::D) 
				&& Input::KeyP(eKeyCode::S))
			{
				mDirection = true;
				pos.x += (speed / 1.5f) * Time::DeltaTime();
				pos.y -= (speed / 1.5f) * Time::DeltaTime();
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
		if (mTime >= mOwner->GetChar()->GetStat().mCoolDown)
		{
			object::Instantiate<Bullet_CheeseArrow>(eLayerType::Player_Bullet, SceneManager::GetActiveScene());
			mTime = 0.0f;
		}
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
		if (Input::GetAnyKey())
		{
			isPlayed = false;
			mFSMState = ePlayerFSM::Move;
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