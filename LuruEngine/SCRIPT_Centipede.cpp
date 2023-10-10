#include "SCRIPT_Centipede.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Gobj_Player.h"
#include <random>

#include "Bullet_BigGreenOrb.h"
#include "Bullet_GreenOrb.h"
#include "Melee_WormEggs.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	void SCRIPT_Centipede::Initialize()
	{
		mOwner = (Gobj_Monster*)GetOwner();
		mTarget = Player;
		mFSMState = eFSMState::Spwan;
		mDirection = false;
		mDeath = false;
		mLaunched = false;
		mAttackNum = false;
		mTime = 0.0f;
		mTime2 = 0.0f;
		mMove = true;
		mPos = mOwner->GetComp<Transform>()->GetPosition();
	}
	void SCRIPT_Centipede::Update()
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();

		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();


		// 필수
		if (mOwner->GetStat().mCurHP <= 0)
			mFSMState = eFSMState::Death;
		if (mTarget == nullptr || mTarget->GetState() == GameObject::eState::Dead)
			mFSMState = eFSMState::Idle;

		if (pos.x <= ppos.x)
			mDirection = true;
		else
			mDirection = false;

		switch (mFSMState)
		{
		case sg::SCRIPT_Centipede::eFSMState::Spwan:
			Spawn();
			break;
		case sg::SCRIPT_Centipede::eFSMState::Idle:
			Idle();
			break;
		case sg::SCRIPT_Centipede::eFSMState::Move:
			Move();
			break;
		case sg::SCRIPT_Centipede::eFSMState::Move2:
			Move2();
			break;
		case sg::SCRIPT_Centipede::eFSMState::Attack:
			Attack();
			break;
		case sg::SCRIPT_Centipede::eFSMState::Attacked:
			Attacked();
			break;
		case sg::SCRIPT_Centipede::eFSMState::Death:
			Death();
			break;
		}
	}
	void SCRIPT_Centipede::OnCollisionEnter(Collider2D* other)
	{
		Gobj_Bullet* bullet = dynamic_cast<Gobj_Bullet*>(other->GetOwner());

		if (other->GetOwner() == bullet)
		{
			int hp = mOwner->GetStat().mCurHP;
			Gobj_Character::CharStat pStat = bullet->GetBulletOwner()->GetStat();
			hp -= (pStat.mStrength * pStat.mDamageScaling) - (pStat.mStrength * mOwner->GetStat().mDefence);
			mOwner->SetStatHP(hp);
		}
	}
	void SCRIPT_Centipede::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_Centipede::OnCollisionExit(Collider2D* other)
	{
	}
	void SCRIPT_Centipede::Spawn()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(spawn), false, mDirection);
		if (mOwner->GetComp<Animator>()->GetActiveAni()->IsComplete())
			mFSMState = eFSMState::Idle;
	}
	void SCRIPT_Centipede::Idle()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(idle), true, mDirection);
		mLaunched = false;

		if (GetDistance() > mOwner->GetStat().mRange)
		{
			mFSMState = eFSMState::Move;
		}
		else
		{
			mFSMState = eFSMState::Attack;
		}
	}
	void SCRIPT_Centipede::Move()
	{
		Animator* at = mOwner->GetComp<Animator>();
		at->PlayAnimation(AnimationName(move1), false, mDirection);
		
		if (at->GetActiveAni()->GetKey() == AnimationName(move1)
			&& at->GetActiveAni()->IsComplete())
		{
			mFSMState = eFSMState::Move2;
			Vector3 pos = mTarget->GetComp<Transform>()->GetPosition();
			mOwner->GetComp<Transform>()->SetPosition(sgRandomPos(pos, 100.0f));
		}

	}
	void SCRIPT_Centipede::Move2()
	{
		Animator* at = mOwner->GetComp<Animator>();
		at->PlayAnimation(AnimationName(move2), false, mDirection);

		if (at->GetActiveAni()->GetKey() == AnimationName(move2)
			&& at->GetActiveAni()->IsComplete())
		{
			mFSMState = eFSMState::Attack;
		}
	}
	void SCRIPT_Centipede::Attack()
	{
		if (GetDistance() >= mOwner->GetStat().mRange)
			mFSMState = eFSMState::Move;

		SelectAttack();
		mTime += Time::DeltaTime();
		Animator* at = mOwner->GetComp<Animator>();
		int index = at->GetActiveAni()->GetAniIndex();

		if (mLaunched)
		{
			mFSMState = eFSMState::Idle;
			return;
		}

		if (mAttackNum == 0) // big orb
		{
			if (mTime >= mOwner->GetStat().mCooldown)
			{
				at->PlayAnimation(AnimationName(attack), false, mDirection);
				mTime = 0.0f;
				mLaunched = false;
			}

			if (index == 8
				&& at->GetActiveAni()->GetKey() == AnimationName(attack))
			{
				object::Instantiate<Bullet_BigGreenOrb>(mOwner, eLayerType::Monster_Bullet, SceneManager::GetActiveScene());
				mLaunched = true;
			}
		}
		else if (mAttackNum == 1) // spawn scarabs
		{
			Vector3 pos = mOwner->GetComp<Transform>()->GetPosition();
			pos.y -= 30.0f;

			if (mTime >= mOwner->GetStat().mCooldown)
			{
				at->PlayAnimation(AnimationName(attack2), false, mDirection);
				mTime = 0.0f;
				mLaunched = false;
			}
			if (index == 9
				&& at->GetActiveAni()->GetKey() == AnimationName(attack2))
			{
				object::Instantiate<Melee_WormEggs>(pos, eLayerType::Monster, SceneManager::GetActiveScene());
				mLaunched = true;
			}
		}
		else if (mAttackNum == 2) // spread orbs
		{
			mTime2 += Time::DeltaTime();
			if (mTime >= mOwner->GetStat().mCooldown)
			{
				mOrbNum = 0;
				mLaunched = false;
				at->PlayAnimation(AnimationName(attack3), false, mDirection);
				mTime = 0.0f;
			}
			if (index > 5
				&& index < 10
				&& at->GetActiveAni()->GetKey() == AnimationName(attack3)
				&& mLaunched == false)
			{
				if (mTime2 >= 0.03f)
				{
					object::Instantiate<Bullet_GreenOrb>(mOwner, eLayerType::Monster_Bullet, SceneManager::GetActiveScene());
					mTime2 = 0.0f;
					mOrbNum++;
				}
				if (mOrbNum >= 8)
				{
					mLaunched = true;
				}
			}
		}

	}
	void SCRIPT_Centipede::Attacked()
	{
	}
	void SCRIPT_Centipede::Death()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(death), false, mDirection);
		if (mOwner->GetComp<Animator>()->GetActiveAni()->IsComplete())
		{
			mOwner->SetState(GameObject::eState::Dead);
		}

	}
	std::wstring SCRIPT_Centipede::AnimationName(const std::wstring& animation)
	{
		if (mOwner)
		{
			std::wstring animationName = L"Ani_";
			animationName += mOwner->GetName();
			animationName += L"_";
			animationName += animation;
			return animationName;
		}
		else
			return L"";
	}
	float SCRIPT_Centipede::GetDistance()
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		return (ppos - pos).Length();
	}
	Vector3 SCRIPT_Centipede::GetDirection()
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		return ppos - pos;
	}
	void SCRIPT_Centipede::SelectAttack()
	{
		std::random_device rd;  // 랜덤 시드를 얻기 위한 장치
		std::mt19937 gen(rd());  // 메르센 트위스터 난수 생성기 초기화
		std::uniform_int_distribution<> dist(0, 2); // 0 ~ 3 랜덤

		mAttackNum = dist(gen);
	}

}