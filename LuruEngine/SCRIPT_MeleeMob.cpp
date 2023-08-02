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
		mTarget = Player;
		mFSMState = eFSMState::Spwan;
		mDirection = false;
		mDeath = false;
	}
	void SCRIPT_MeleeMob::Update()
	{
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
		case sg::SCRIPT_MeleeMob::eFSMState::Spwan:
			Spawn();
			break;
		case sg::SCRIPT_MeleeMob::eFSMState::Idle:
			Idle();
			break;
		case sg::SCRIPT_MeleeMob::eFSMState::Move:
			Move();
			break;
		case sg::SCRIPT_MeleeMob::eFSMState::Attack:
			Attack();
			break;
		case sg::SCRIPT_MeleeMob::eFSMState::Attacked:
			Attacked();
			break;
		case sg::SCRIPT_MeleeMob::eFSMState::Death:
			Death();
			break;
		}


	}
	void SCRIPT_MeleeMob::LateUpdate()
	{
	}
	void SCRIPT_MeleeMob::Render()
	{
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
		mFSMState = eFSMState::Idle;
	}
	void SCRIPT_MeleeMob::Idle()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(idle), true, mDirection);
		mAttacked = false;

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
	void SCRIPT_MeleeMob::Move()
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
	void SCRIPT_MeleeMob::Attack()
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
	void SCRIPT_MeleeMob::Attacked()
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
}