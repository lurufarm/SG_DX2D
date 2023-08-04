#include "SCRIPT_RangedMob.h"
#include "Monster_Ranged.h"
#include "Gobj_Player.h"
#include "Gobj_Character.h"
#include "Gobj_Bullet.h"

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
	}
	void SCRIPT_RangedMob::Update()
	{
		mTime += Time::DeltaTime();

		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();

		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		// ÇÊ¼ö
		if (mOwner->GetStat().mHP <= 0)
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

				stat.mHP -= mOwner->GetStat().mStrength;

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

		//if (mTime >= mOwner->GetStat().)

		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();
		Vector3 direction = ppos - pos;
		if (direction.Length() > mOwner->GetStat().mRange)
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
		Transform* ptr = mTarget->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		float distance = (ppos - pos).Length();
		float distanceToMove = mOwner->GetStat().mSpeed * Time::DeltaTime();
		Vector3 direction = ppos - pos;
		direction.Normalize();
		pos += direction * distanceToMove;
		tr->SetPosition(pos);

		if (distance <= mOwner->GetStat().mRange)
			mFSMState = eFSMState::Attack;
	}
	void SCRIPT_RangedMob::Attack()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(attack), true, mDirection);

		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		Vector3 direction = ppos - pos;

		if (direction.Length() > mOwner->GetStat().mRange)
		{
			mFSMState = eFSMState::Move;
		}
	}
	void SCRIPT_RangedMob::Attacked()
	{
		if (mAttacked == false)
		{
			mAttacked = true;
			mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(attacked), false, mDirection);
			int hp = mOwner->GetStat().mHP;
			hp -= mTarget->GetStat().mStrength;
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
}