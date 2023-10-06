#include "SCRIPT_MeleeMob.h"
#include "Monster_Melee.h"
#include "Gobj_Player.h"
#include "Gobj_Character.h"
#include "Gobj_Bullet.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	SCRIPT_MeleeMob::SCRIPT_MeleeMob()
		: mOwner(nullptr)
	{

	}
	SCRIPT_MeleeMob::~SCRIPT_MeleeMob()
	{
	}
	void SCRIPT_MeleeMob::Initialize()
	{
		mOwner = (Monster_Melee*)GetOwner();
		mColSize = mOwner->GetComp<Collider2D>()->GetCSize();
		mTarget = Player;
		mFSMState = eFSMState::Spwan;
		mDirection = false;
		mDeath = false;
	}
	void SCRIPT_MeleeMob::Update()
	{

		// ÇÊ¼ö
		if (mOwner->GetStat().mCurHP <= 0)
			mFSMState = eFSMState::Death;
		if (mTarget == nullptr || mTarget->GetState() == GameObject::eState::Dead)
			mFSMState = eFSMState::Idle;

		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();

		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		if (pos.x <= ppos.x)
			mDirection = true;
		else
			mDirection = false;

		switch (mFSMState)
		{
		case sg::SCRIPT_MeleeMob::eFSMState::Spwan:
			Spawn();
			break;
		case sg::SCRIPT_MeleeMob::eFSMState::Idle:
			mOwner->GetComp<Collider2D>()->SetSize(mColSize);
			Idle();
			break;
		case sg::SCRIPT_MeleeMob::eFSMState::Move:
			mOwner->GetComp<Collider2D>()->SetSize(mColSize);
			Move();
			break;
		case sg::SCRIPT_MeleeMob::eFSMState::Attack:
			mOwner->GetComp<Collider2D>()->SetSize(Vector2(1.0f, 1.0f));
			Attack();
			break;
		case sg::SCRIPT_MeleeMob::eFSMState::Attacked:
			mOwner->GetComp<Collider2D>()->SetSize(mColSize);
			Attacked();
			break;
		case sg::SCRIPT_MeleeMob::eFSMState::Death:
			mOwner->GetComp<Collider2D>()->SetSize(mColSize);
			Death();
			break;
		}


	}

	void SCRIPT_MeleeMob::OnCollisionEnter(Collider2D* other)
	{
		if (other->GetOwner() == dynamic_cast<Gobj_Bullet*>(other->GetOwner()))
		{
			if (mAttacked == false)
			{
				mFSMState = eFSMState::Attacked;
			}
		}
	}
	void SCRIPT_MeleeMob::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_MeleeMob::OnCollisionExit(Collider2D* other)
	{
		if (other->GetOwner() == dynamic_cast<Gobj_Bullet*>(other->GetOwner()))
		{
			mAttacked = false;
		}
	}
	void SCRIPT_MeleeMob::Spawn()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(spawn), false, mDirection);
		if (mOwner->GetComp<Animator>()->GetActiveAni()->IsComplete())
			mFSMState = eFSMState::Idle;
	}
	void SCRIPT_MeleeMob::Idle()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(idle), true, mDirection);
		mAttacked = false;

		if (GetDistance() > mOwner->GetStat().mRange * 1.5f)
		{
			mFSMState = eFSMState::Move;
		}
		else
		{
			mFSMState = eFSMState::Attack;
		}
	}
	void SCRIPT_MeleeMob::Move()
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
	void SCRIPT_MeleeMob::Attack()
	{
		mTime += Time::DeltaTime();

		Animator* at = mOwner->GetComp<Animator>();
		int Index = at->GetActiveAni()->GetAniIndex();
		std::wstring ownerName = mOwner->GetName();
		if (mTime >= mOwner->GetStat().mCooldown)
		{
			at->PlayAnimation(AnimationName(attack), false, mDirection);
			mTime = 0.0f;
		}

		if (GetDistance() > mOwner->GetStat().mRange * 1.5f)
			mFSMState = eFSMState::Move;

		else if (at->GetActiveAni()->IsComplete())
		{
			mFSMState = eFSMState::Idle;
			at->PlayAnimation(AnimationName(idle), true, mDirection);
		}

		if (at->GetActiveAni()->GetKey() == AnimationName(attack))
		{
			if (ownerName == L"SlimeA" || ownerName == L"SlimeB" || ownerName == L"EliteCannibals")
			{
				if (Index == 4)
					mAttackable = true;
				else
					mAttackable = false;
			}
			else if (ownerName == L"Larva" || ownerName == L"EliteLarva")
			{
				if (Index == 3)
					mAttackable = true;
				else
					mAttackable = false;
			}
			else if (ownerName == L"Cannibals")
			{
				if (Index == 3)
					mAttackable = true;
				else
					mAttackable = false;
			}
			else if (ownerName == L"Bat")
			{
				if (Index == 4)
					mAttackable = true;
				else
					mAttackable = false;
			}
			else if (ownerName == L"Zombie")
			{
				if (Index == 5)
					mAttackable = true;
				else
					mAttackable = false;
			}
			else if (ownerName == L"Skeleton")
			{
				if (Index == 3)
					mAttackable = true;
				else
					mAttackable = false;
			}
			else if (ownerName == L"Bee" || ownerName == L"EliteBee")
			{
				if (Index == 3)
					mAttackable = true;
				else
					mAttackable = false;
			}
			else if (ownerName == L"LizardSword")
			{
				if (Index == 2)
					mAttackable = true;
				else
					mAttackable = false;
			}
			else if (ownerName == L"Snake")
			{
				if (Index == 1)
					mAttackable = true;
				else
					mAttackable = false;
			}
			else if (ownerName == L"Mummy")
			{
				if (Index == 3)
					mAttackable = true;
				else
					mAttackable = false;
			}
			else
			{
				mAttackable = false;
			}
		}
		else
		{
			mAttackable = false;
		}
	}
	void SCRIPT_MeleeMob::Attacked()
	{
		if (mAttacked == false)
		{
			mAttacked = true;
			mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(attacked), false, mDirection);
			int hp = mOwner->GetStat().mCurHP;
			Gobj_Character::CharStat pStat = mTarget->GetStat();
			hp -= (pStat.mStrength * pStat.mDamageScaling) - (pStat.mStrength * mOwner->GetStat().mDefence);
			mOwner->SetStatHP(hp);
		}
		if (mOwner->GetComp<Animator>()->GetActiveAni()->IsComplete())
		{
			mFSMState = eFSMState::Idle;
		}
	}
	void SCRIPT_MeleeMob::Death()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(death), false, mDirection);
		if (mOwner->GetComp<Animator>()->GetActiveAni()->IsComplete())
			mOwner->SetState(GameObject::eState::Dead);
	}
	std::wstring SCRIPT_MeleeMob::AnimationName(const std::wstring& animation)
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
	float SCRIPT_MeleeMob::GetDistance()
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		return (ppos - pos).Length();
	}
	Vector3 SCRIPT_MeleeMob::GetDirection()
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		return ppos - pos;
	}
}