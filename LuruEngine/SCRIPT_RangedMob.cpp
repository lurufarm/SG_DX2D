#include "SCRIPT_RangedMob.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Monster_Ranged.h"
#include "Gobj_Player.h"
#include "Gobj_Character.h"
#include "Gobj_Bullet.h"
#include "Bullet_PoisonOrb.h"
#include "Bullet_EntRock.h"
#include "Effect_ProjectileDest.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	SCRIPT_RangedMob::SCRIPT_RangedMob()
		: mOwner(nullptr)
	{
	}
	SCRIPT_RangedMob::~SCRIPT_RangedMob()
	{
	}
	void SCRIPT_RangedMob::Initialize()
	{
		mOwner = (Monster_Ranged*)GetOwner();
		mTarget = Player;
		mFSMState = eFSMState::Spwan;
		mDirection = false;
		mDeath = false;
		mLaunched = false;
	}
	void SCRIPT_RangedMob::Update()
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();

		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		// ÇÊ¼ö
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
		case sg::SCRIPT_RangedMob::eFSMState::Spwan:
			Spawn();
			break;
		case sg::SCRIPT_RangedMob::eFSMState::Idle:
			Idle();
			break;
		case sg::SCRIPT_RangedMob::eFSMState::Move:
			Move();
			break;
		case sg::SCRIPT_RangedMob::eFSMState::Attack:
			Attack();
			break;
		case sg::SCRIPT_RangedMob::eFSMState::Attacked:
			Attacked();
			break;
		case sg::SCRIPT_RangedMob::eFSMState::Death:
			Death();
			break;
		}
	}
	void SCRIPT_RangedMob::LateUpdate()
	{
	}
	void SCRIPT_RangedMob::Render()
	{
	}
	void SCRIPT_RangedMob::OnCollisionEnter(Collider2D* other)
	{
		if (other->GetOwner() == dynamic_cast<Gobj_Bullet*>(other->GetOwner()))
		{
			if (mAttacked == false)
			{
				mFSMState = eFSMState::Attacked;
			}
		}
		if (mFSMState == eFSMState::Attack)
		{
			if (other->GetOwner() == mTarget)
			{
				Gobj_Character::CharStat stat = mTarget->GetStat();

				stat.mCurHP -= mOwner->GetStat().mStrength;

				mTarget->SetStat(stat);
			}
		}
	}
	void SCRIPT_RangedMob::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_RangedMob::OnCollisionExit(Collider2D* other)
	{
		if (other->GetOwner() == dynamic_cast<Gobj_Bullet*>(other->GetOwner()))
		{
			mAttacked = false;
		}
	}
	void SCRIPT_RangedMob::Spawn()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(spawn), false, mDirection);
		if (mOwner->GetComp<Animator>()->GetActiveAni()->IsComplete())
			mFSMState = eFSMState::Idle;
	}
	void SCRIPT_RangedMob::Idle()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(idle), true, mDirection);
		mAttacked = false;
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
	void SCRIPT_RangedMob::Move()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(move), true, mDirection);

		Transform* tr = mOwner->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();

		float distance = GetDistance();
		float distanceToMove = mOwner->GetStat().mSpeed * Time::DeltaTime();
		Vector3 direction = GetDirection();
		direction.Normalize();
		pos += direction * distanceToMove;
		tr->SetPosition(pos);

		if (distance <= mOwner->GetStat().mRange)
			mFSMState = eFSMState::Attack;
	}
	void SCRIPT_RangedMob::Attack()
	{
		if (GetDistance() > mOwner->GetStat().mRange)
		{
			mFSMState = eFSMState::Move;
		}

		mTime += Time::DeltaTime();

		Animator* at = mOwner->GetComp<Animator>();
		if (mTime >= mOwner->GetStat().mCooldown)
		{
			at->PlayAnimation(AnimationName(attack), false, mDirection);
			mTime = 0.0f;
		}		

		if (mOwner->GetName() == L"CannibalFlowerA")
		{
			if (at->GetActiveAni()->GetAniIndex() == 3 
				&& at->GetActiveAni()->GetKey() == AnimationName(attack)
				&& mLaunched == false)
			{
				Bullet_PoisonOrb* pob = object::Instantiate<Bullet_PoisonOrb>(mOwner, eLayerType::Monster_Bullet, SceneManager::GetActiveScene());
				mLaunched = true;
			}
		}
		else if (mOwner->GetName() == L"Ent")
		{
			if (at->GetActiveAni()->GetAniIndex() == 7 
				&& at->GetActiveAni()->GetKey() == AnimationName(attack) 
				&& mLaunched == false)
			{
				Vector3 pos = mTarget->GetComp<Transform>()->GetPosition();
				pos.z += 0.1f;
				Effect_ProjectileDest* epd = object::Instantiate<Effect_ProjectileDest>(pos, eLayerType::Effect, SceneManager::GetActiveScene());
				Bullet_EntRock* erk = object::Instantiate<Bullet_EntRock>(mOwner, eLayerType::Monster_Bullet, SceneManager::GetActiveScene());
				mLaunched = true;
			}
		}

		if (mLaunched && at->GetActiveAni()->IsComplete())
		{
			at->PlayAnimation(AnimationName(idle), true, mDirection);
			mFSMState = eFSMState::Idle;
		}
	}
	void SCRIPT_RangedMob::Attacked()
	{
		if (mAttacked == false)
		{
			mAttacked = true;
			mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(attacked), false, mDirection);
			Gobj_Character::CharStat pStat = mTarget->GetStat();
			int hp = mOwner->GetStat().mCurHP;
			hp -= pStat.mStrength * pStat.mDamageScaling;
			mOwner->SetStatHP(hp);
		}
		if (mOwner->GetComp<Animator>()->GetActiveAni()->IsComplete())
		{
			mFSMState = eFSMState::Idle;
		}
	}
	void SCRIPT_RangedMob::Death()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(death), false, mDirection);
		if (mOwner->GetComp<Animator>()->GetActiveAni()->IsComplete())
			mOwner->SetState(GameObject::eState::Dead);
	}
	std::wstring SCRIPT_RangedMob::AnimationName(const std::wstring& animation)
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
	float SCRIPT_RangedMob::GetDistance()
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		return (ppos - pos).Length();
	}
	Vector3 SCRIPT_RangedMob::GetDirection()
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		return ppos - pos;
	}
}