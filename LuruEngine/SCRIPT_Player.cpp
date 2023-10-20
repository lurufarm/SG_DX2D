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
#include "Monsters.h"
#include "Monster_Melee.h"
#include "Monster_Ranged.h"
#include "Bullet_CheeseArrow.h"
#include "Bullet_LucyBomb.h"
#include "Bullet_RoboBeam.h"
#include "Bullet_SzilaFire.h"

#include "SCRIPT_MeleeMob.h"
#include "SCRIPT_MeleeZombie.h"
#include "SCRIPT_MobProjectile.h"
#include "SCRIPT_SkelKnight.h"
#include "SCRIPT_Centipede.h"
#include "Effect_OldEntStem.h"
#include "Effect_LaserFiring.h"
#include "Effect_MobExplosion.h"


extern sg::Gobj_Player* Player;

namespace sg
{
	void SCRIPT_Player::Initialize()
	{
		mFSMState = ePlayerFSM::Idle;
		mOwner = (Gobj_Player*)GetOwner();
		mDirection = true;
		mTime = 0.0f;
		mAttackedTime = 0.0f;
		mAttacked = false;
		mDeath = false;
		mAttackedDir = Vector3::Zero;
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
			mAttackedTime += Time::DeltaTime();
			if (mAttackedTime >= 0.5f)
			{
				mAttacked = false;
				mAttackedTime = 0.0f;
			}
				
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
				if (distanceOfMob.begin()->first <= mOwner->GetChar()->GetStat().mRange * 2.0f)
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
	}

	void SCRIPT_Player::DeductPlayerHP(Gobj_Character::CharStat& pStat, float damage)
	{
		pStat.mCurHP -= damage * pStat.mDefence;
		mOwner->SetStat(pStat);
	}
	void SCRIPT_Player::DeductPlayerHP(Gobj_Character::CharStat& pStat, GameObject* attacker)
	{
		if (attacker != nullptr)
		{
			Gobj_Monster::MobStat mobStat = static_cast<Gobj_Monster*>(attacker)->GetStat();
			pStat.mCurHP -= mobStat.mStrength - (mobStat.mStrength * pStat.mDefence);
			mOwner->SetStat(pStat);
		}
	}

	void SCRIPT_Player::OnCollisionEnter(Collider2D* other)
	{
		GameObject* otherOwner = other->GetOwner();
		SCRIPT_SkelKnight* skelKnight = otherOwner->GetComp<SCRIPT_SkelKnight>();
		SCRIPT_Centipede* centiped = otherOwner->GetComp<SCRIPT_Centipede>();

		if (skelKnight != nullptr || centiped == nullptr)
			mOwner->SetTransParent(true);

		if (mDeath || mAttacked)
			return;

		mAttackedDir = GetAttackedDir(otherOwner);
		SCRIPT_MobProjectile* mobProj = otherOwner->GetComp<SCRIPT_MobProjectile>();
		Gobj_Character::CharStat pStat = mOwner->GetStat();
		if (mobProj != nullptr && mobProj->GetProjActivated())
		{
			mAttacked = true;
			DeductPlayerHP(pStat, mobProj->GetProjOwner());
		}

	}
	void SCRIPT_Player::OnCollisionStay(Collider2D* other)
	{
		GameObject* otherOwner = other->GetOwner();
		SCRIPT_SkelKnight* skelKnight = otherOwner->GetComp<SCRIPT_SkelKnight>();

		//if (skelKnight != nullptr)
		//	mOwner->SetTransParent(true);

		if (mDeath || mAttacked)
			return;

		mAttackedDir = GetAttackedDir(otherOwner);
		SCRIPT_MeleeMob* meleeMob = otherOwner->GetComp<SCRIPT_MeleeMob>();
		SCRIPT_MobProjectile* mobProj = otherOwner->GetComp<SCRIPT_MobProjectile>();
		Gobj_Effect* effect = otherOwner->GetComp<Gobj_Effect>();
		Gobj_Character::CharStat pStat = mOwner->GetStat();

		if (meleeMob != nullptr && meleeMob->mAttackable)
		{
			mAttacked = true;
			DeductPlayerHP(pStat, meleeMob->GetOwner());
		}
		else if (mobProj != nullptr && mobProj->GetProjActivated())
		{
			mAttackedDir = GetAttackedDir(mobProj);
			mAttacked = true;
			DeductPlayerHP(pStat, mobProj->GetProjOwner());
		}
		else if (skelKnight != nullptr && skelKnight->mAttackable)
		{
			mAttacked = true;
			mOwner->SetTransParent(true);
			DeductPlayerHP(pStat, skelKnight->GetOwner());
		}
		else if (effect != nullptr)
		{
			mAttacked = true;
			DeductPlayerHP(pStat, 8.0f);
		}
	}
	void SCRIPT_Player::OnCollisionExit(Collider2D* other)
	{
		mOwner->SetTransParent(false);
	}


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
		int Index = mAni->GetActiveAni()->GetAniIndex();
		if (mOwner->GetEnemyNearby() == false)
		{
			mFSMState = ePlayerFSM::Idle;
		}
		if (mTime >= mOwner->GetStat().mCooldown && mOwner->GetStat().mRange * 2.0f >= GetDistanceToEnemy())
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
			else if (mOwner->GetChar()->GetName() == L"Robo")
			{
				int RoboBeamRange = (int)(mOwner->GetStat().mRange - 100.0f) / 100.0f;
				Vector3 epos = mOwner->GetComp<Transform>()->GetPosition();
				epos.z -= 2.0f;
				object::Instantiate<Effect_LaserFiring>(epos, eLayerType::Player_Effect, SceneManager::GetActiveScene());
				object::ShootBullet<Bullet_RoboBeam>(RoboBeamRange, eLayerType::Player_Beam, SceneManager::GetActiveScene());
			}
			else if (mOwner->GetChar()->GetName() == L"Szila")
			{
				object::ShootBullet<Bullet_SzilaFire>(mOwner->GetStat().mProjectileCount, eLayerType::Player_Bullet, SceneManager::GetActiveScene());
			}

			mTime = 0.0f;
		}
		if (Input::GetAnyKey())
			mFSMState = ePlayerFSM::Move;
		else if (Input::GetAnyKey() == false && mAni->GetActiveAni()->IsComplete())
		{
			mFSMState = ePlayerFSM::Idle;
			mAni->PlayAnimation(AnimationName(idle), true, mDirection);
		}
	}
	void SCRIPT_Player::Attacked()
	{
		Animator* mAni = mOwner->GetComp<Animator>();
		mAni->PlayAnimation(AnimationName(attacked), false, mDirection);
		mTime = 0.0f;
		Transform* tr = mOwner->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();

		if (mAttacked)
		{
			pos += mAttackedDir * 20.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (mAni->GetActiveAni()->GetKey() == AnimationName(attacked) && mAni->GetActiveAni()->IsComplete())
		{
			mFSMState = ePlayerFSM::Idle;
		}
		if (Input::GetAnyKey() && mAni->GetActiveAni()->IsComplete() && mAni->GetActiveAni()->GetKey() == AnimationName(attacked))
		{
			mFSMState = ePlayerFSM::Move;
		}
		if (mOwner->GetStat().mCurHP <= 0)
		{
			mAttacked = false;
			mDeath = true;
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


	std::wstring SCRIPT_Player::AnimationName(const std::wstring& animation)
	{
		std::wstring animationName = L"Ani_";
		animationName += mOwner->GetChar()->GetName();
		animationName += L"_";
		animationName += animation;
		return animationName;
	}
}