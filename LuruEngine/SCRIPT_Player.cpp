#include "SCRIPT_Player.h"

#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgGameObject.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "..\Engine_SOURCE\sgTransform.h"
#include "..\Engine_SOURCE\sgAnimator.h"

#include "SCENE_PlayScene.h"
#include "Gobj_Player.h"
#include "Gobj_Bullet.h"
#include "Gobj_Monster.h"
#include "Monster_Melee.h"
#include "Monster_Ranged.h"
#include "Bullet_CheeseArrow.h"
#include "Bullet_LucyBomb.h"

#include "SCRIPT_MeleeMob.h"
#include "SCRIPT_MobProjectile.h"
#include "Effect_OldEntStem.h"


extern sg::Gobj_Player* Player;

namespace sg
{
	void SCRIPT_Player::Initialize()
	{
		mFSMState = ePlayerFSM::Idle;
		mOwner = (Gobj_Player*)GetOwner();
		mDirection = true;
		mTime = 0.0f;
		mAttacked = false;
		mDeath = false;
	}

	void SCRIPT_Player::Update()
	{

		if (mOwner->GetStat().mCurHP <= 0)
		{
			mDeath = true;
			mFSMState = ePlayerFSM::Death;
		}
		if (mAttacked)
		{
			mFSMState = ePlayerFSM::Attacked;
		}
		else
		{
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
						mDirection = true;
					else
						mDirection = false;
				}
				else
					mOwner->SetEnemyNearby(false);
			}
			else
			{
				mOwner->SetEnemyNearby(false);
			}
		}
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
		case sg::SCRIPT_Player::ePlayerFSM::Death:
			Death();
			break;
		}

		if (Input::GetAnyKey())
		{
			mKey = Input::GetAnyKeyInfo();
			mFSMState = ePlayerFSM::Move;
		}
		else
		{
			mFSMState = ePlayerFSM::Idle;
			if (mOwner->GetEnemyNearby() && mAttacked == false && mDeath == false)
				mFSMState = ePlayerFSM::Attack;
		}
	};

	void SCRIPT_Player::Idle()
	{
		Animator* mAni = GetOwner()->GetComp<Animator>();
		mAni->PlayAnimation(AnimationName(idle), true, mDirection);

		if (mOwner->GetEnemyNearby())
			mFSMState = ePlayerFSM::Attack;
		else if (Input::GetAnyKey())
			mFSMState = ePlayerFSM::Move;
	}
	void SCRIPT_Player::Move(Input::Key key, float speed)
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Animator* mAni = GetOwner()->GetComp<Animator>();

		if (Input::GetAnyKey())
		{
			mKey = Input::GetAnyKeyInfo();

			if (mKey.key == eKeyCode::A 
				&& Input::GetKeyState(eKeyCode::W) == eKeyState::None 
				&& Input::GetKeyState(eKeyCode::S) == eKeyState::None)
			{
				mDirection = false;
				pos.x -= speed * Time::DeltaTime();
				tr->SetPosition(pos);
				mAni->PlayAnimation(AnimationName(move), true, mDirection);
			}
			else if (mKey.key == eKeyCode::D 
				&& Input::GetKeyState(eKeyCode::W) == eKeyState::None 
				&& Input::GetKeyState(eKeyCode::S) == eKeyState::None)
			{
				mDirection = true;
				pos.x += speed * Time::DeltaTime();
				tr->SetPosition(pos);
				mAni->PlayAnimation(AnimationName(move), true, mDirection);
			}
			else if (mKey.key == eKeyCode::W 
				&& Input::GetKeyState(eKeyCode::A) == eKeyState::None 
				&& Input::GetKeyState(eKeyCode::D) == eKeyState::None)
			{
				pos.y += speed * Time::DeltaTime();
				tr->SetPosition(pos);
				mAni->PlayAnimation(AnimationName(move), true, mDirection);
			}
			else if (mKey.key == eKeyCode::S 
				&& Input::GetKeyState(eKeyCode::A) == eKeyState::None 
				&& Input::GetKeyState(eKeyCode::D) == eKeyState::None)
			{
				pos.y -= speed * Time::DeltaTime();
				tr->SetPosition(pos);
				mAni->PlayAnimation(AnimationName(move), true, mDirection);
			}
			
			if (Input::KeyP(eKeyCode::A) 
				&& Input::KeyP(eKeyCode::W))
			{
				mDirection = false;
				pos.x -= (speed / 1.5f) * Time::DeltaTime();
				pos.y += (speed / 1.5f) * Time::DeltaTime();
				tr->SetPosition(pos);
				mAni->PlayAnimation(AnimationName(move), true, mDirection);
			}
			else if (Input::KeyP(eKeyCode::A) 
				&& Input::KeyP(eKeyCode::S))
			{
				mDirection = false;
				pos.x -= (speed / 1.5f) * Time::DeltaTime();
				pos.y -= (speed / 1.5f) * Time::DeltaTime();
				tr->SetPosition(pos);
				mAni->PlayAnimation(AnimationName(move), true, mDirection);
			}
			else if (Input::KeyP(eKeyCode::D) 
				&& Input::KeyP(eKeyCode::W))
			{
				mDirection = true;
				pos.x += (speed / 1.5f) * Time::DeltaTime();
				pos.y += (speed / 1.5f) * Time::DeltaTime();
				tr->SetPosition(pos);
				mAni->PlayAnimation(AnimationName(move), true, mDirection);
			}
			else if (Input::KeyP(eKeyCode::D) 
				&& Input::KeyP(eKeyCode::S))
			{
				mDirection = true;
				pos.x += (speed / 1.5f) * Time::DeltaTime();
				pos.y -= (speed / 1.5f) * Time::DeltaTime();
				tr->SetPosition(pos);
				mAni->PlayAnimation(AnimationName(move), true, mDirection);
			}
		}
		if (Input::GetAnyKey() == false)
		{
			mAni->PlayAnimation(AnimationName(idle), true, mDirection);

			if (mOwner->GetEnemyNearby())
				mFSMState = ePlayerFSM::Attack;
			else
				mFSMState = ePlayerFSM::Idle;
		}
	}
	void SCRIPT_Player::Attack()
	{
		mTime += Time::DeltaTime();
		Animator* mAni = GetOwner()->GetComp<Animator>();
		if (mOwner->GetEnemyNearby() == false)
		{
			mFSMState = ePlayerFSM::Idle;
		}
		if (mTime >= mOwner->GetChar()->GetStat().mCooldown)
		{
			mAni->PlayAnimation(AnimationName(attack), false, mDirection);
			if (mOwner->GetChar()->GetName() == L"Cheese")
			{
				for (size_t i = 1; i <= mOwner->GetStat().mProjectileCount; i++)
				{
					object::ShootBullet<Bullet_CheeseArrow>(i, eLayerType::Player_Bullet, SceneManager::GetActiveScene());
				}
			}
			else if (mOwner->GetChar()->GetName() == L"Lucy")
			{
				for (size_t i = 1; i <= mOwner->GetStat().mProjectileCount; i++)
				{
					object::ShootBullet<Bullet_LucyBomb>(i, eLayerType::Player_Bullet, SceneManager::GetActiveScene());
				}
			}
			mTime = 0.0f;	
		}
		if (Input::GetAnyKey())
			mFSMState = ePlayerFSM::Move;
		else if (Input::GetAnyKey() == false && mAni->GetActiveAni()->IsComplete())
		{
			mFSMState = ePlayerFSM ::Idle;
			mAni->PlayAnimation(AnimationName(idle), true, mDirection);
		}
	}
	void SCRIPT_Player::Attacked()
	{
		Animator* mAni = mOwner->GetComp<Animator>();
		mAni->PlayAnimation(AnimationName(attacked), false, mDirection);
		mTime = 0.0f;

		if (mAni->GetActiveAni()->IsComplete() && mAni->GetActiveAni()->GetKey() == AnimationName(attacked))
		{
			mAttacked = false;
			mFSMState = ePlayerFSM::Idle;
		}
		if (Input::GetAnyKey() && mAni->GetActiveAni()->IsComplete() && mAni->GetActiveAni()->GetKey() == AnimationName(attacked))
		{
			mAttacked = false;
			mFSMState = ePlayerFSM::Move;
		}
		if (mOwner->GetStat().mCurHP <= 0)
		{
			mAttacked = false;
			mFSMState = ePlayerFSM::Death;
		}

	}
	void SCRIPT_Player::Death()
	{
		Animator* mAni = mOwner->GetComp<Animator>();
		mAni->PlayAnimation(AnimationName(death), false, mDirection);

		if (mAni->GetActiveAni()->GetKey() == AnimationName(death) && mAni->GetActiveAni()->IsComplete())
			SceneManager::LoadScene(L"02_LobbyScene");

	}
	void SCRIPT_Player::OnCollisionEnter(Collider2D* other)
	{
		SCRIPT_MeleeMob* sm = other->GetOwner()->GetComp<SCRIPT_MeleeMob>();
		SCRIPT_MobProjectile* sp = other->GetOwner()->GetComp<SCRIPT_MobProjectile>();
		Effect_OldEntStem* oes = dynamic_cast<Effect_OldEntStem*>(other->GetOwner());
		
		if (sm != nullptr && sm->mAttack && mAttacked == false && mDeath == false)
		{
			mAttacked = true;
			Gobj_Character::CharStat pStat = mOwner->GetStat();
			Gobj_Monster::MobStat mobStat = ((Gobj_Monster*)sm->GetOwner())->GetStat();
			pStat.mCurHP -= mobStat.mStrength - (mobStat.mStrength * pStat.mDefence);
			mOwner->SetStat(pStat);
		}
		else if (sp != nullptr)
		{
			if (mAttacked == false && mDeath == false && sp->GetProjActivated())
			{
				mAttacked = true;
				Gobj_Character::CharStat pStat = mOwner->GetStat();
				if (((Gobj_MobProjectile*)sp->GetOwner())->GetProjOwner() != nullptr)
				{
					Gobj_Monster::MobStat mobStat = ((Gobj_MobProjectile*)sp->GetOwner())->GetProjOwner()->GetStat();
					pStat.mCurHP -= mobStat.mStrength - (mobStat.mStrength * pStat.mDefence);
				}
				else
					pStat.mCurHP -= 8.0f - (8.0f * pStat.mDefence);
				mOwner->SetStat(pStat);
			}
		}
		else if (oes != nullptr)
		{
			if (mAttacked == false && mDeath == false)
			{
				mAttacked = true;
				Gobj_Character::CharStat pStat = mOwner->GetStat();
				pStat.mCurHP -= 8.0f - (8.0f * pStat.mDefence);
				mOwner->SetStat(pStat);
			}
		}
	}
	void SCRIPT_Player::OnCollisionStay(Collider2D* other)
	{
		//SCRIPT_MeleeMob* sm = other->GetOwner()->GetComp<SCRIPT_MeleeMob>();
		//if (sm != nullptr && sm->mAttack && mAttacked == false && mDeath == false)
		//{
		//	mAttacked = true;
		//	Gobj_Character::CharStat pStat = mOwner->GetStat();
		//	Gobj_Monster::MobStat mobStat = ((Gobj_Monster*)sm->GetOwner())->GetStat();
		//	pStat.mCurHP -= mobStat.mStrength - (mobStat.mStrength * pStat.mDefence);
		//	mOwner->SetStat(pStat);
		//}
	}
	void SCRIPT_Player::OnCollisionExit(Collider2D* other)
	{
		mAttacked = false;
		//mFSMState = ePlayerFSM::Idle;
	}
	std::wstring SCRIPT_Player::AnimationName(const std::wstring& animation)
	{
		std::wstring animationName = L"Ani_";
		animationName += mOwner->GetChar()->GetName();
		animationName += L"_";
		animationName += animation;
		return animationName;
	}
}