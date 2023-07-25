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

		if (mOwner->GetStat().mHP <= 0)
			mFSMState = eFSMState::Death;
		if (mTarget == nullptr || mTarget->GetState() == GameObject::eState::Dead)
			mFSMState = eFSMState::Idle;

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



		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();
		
		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		if (pos.x <= ppos.x)
			mDirection = true;
		else
			mDirection = false;

		float distance = (ppos - pos).Length();

		if (distance > mOwner->GetStat().mRange && mDeath == false)
			mFSMState = eFSMState::Move;
		else
			mFSMState = eFSMState::Attack;
		


	}
	void SCRIPT_MeleeMob::LateUpdate()
	{
	}
	void SCRIPT_MeleeMob::Render()
	{
	}
	void SCRIPT_MeleeMob::OnCollisionEnter(Collider2D* other)
	{
		Gobj_Bullet* bullet = dynamic_cast<Gobj_Bullet*>(other->GetOwner());
		if (bullet->GetComp<Collider2D>() == other && mAttacked == false)
		{
			mAttacked = true;
			mFSMState = eFSMState::Attacked;
		}
	}
	void SCRIPT_MeleeMob::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_MeleeMob::OnCollisionExit(Collider2D* other)
	{
		Gobj_Bullet* bullet = dynamic_cast<Gobj_Bullet*>(other->GetOwner());
		if (bullet->GetComp<Collider2D>() == other && mAttacked == true)
		{
			mAttacked = false;
			Update();
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
	}
	void SCRIPT_MeleeMob::Move()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(move), true, mDirection);
		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		Vector3 direction = ppos - pos;
		direction.Normalize();

		// Calculate the distance to move in this frame based on the speed and time
		float distanceToMove = mOwner->GetStat().mSpeed * Time::DeltaTime();

		// If the distance to move is greater than the distance to mTarget, just set the position to mTarget
		if (distanceToMove >= direction.Length())
		{
			tr->SetPosition(ppos);
		}
		else
		{
			// Otherwise, move towards the mTarget with the calculated distance
			pos += direction * distanceToMove;
			tr->SetPosition(pos);
		}

		float distance = (ppos - pos).Length();
		if (distance < mOwner->GetStat().mRange)
			mFSMState = eFSMState::Attack;
	}
	void SCRIPT_MeleeMob::Attack()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(attack), true, mDirection);
	}
	void SCRIPT_MeleeMob::Attacked()
	{
		if (mAttacked)
		{
			mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(attacked), true, mDirection);
			int hp = mOwner->GetStat().mHP;
			hp -= mTarget->GetStat().mStrength;
			mOwner->SetStatHP(hp);
		}
		if (mOwner->GetComp<Animator>()->GetActiveAni()->IsComplete())
			mFSMState = eFSMState::Idle;
		mAttacked = false;

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