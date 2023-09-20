#include "SCRIPT_SkelKnight.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Gobj_Player.h"
#include "Bullet_FireOrb.h"
#include "Bullet_SKGroundFires.h"
#include <random>

extern sg::Gobj_Player* Player;
namespace sg
{
	void SCRIPT_SkelKnight::Initialize()
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
	}
	void SCRIPT_SkelKnight::Update()
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
		case sg::SCRIPT_SkelKnight::eFSMState::Spwan:
			Spawn();
			break;
		case sg::SCRIPT_SkelKnight::eFSMState::Idle:
			Idle();
			break;
		case sg::SCRIPT_SkelKnight::eFSMState::Move:
			Move();
			break;
		case sg::SCRIPT_SkelKnight::eFSMState::Attack:
			Attack();
			break;
		case sg::SCRIPT_SkelKnight::eFSMState::Attacked:
			Attacked();
			break;
		case sg::SCRIPT_SkelKnight::eFSMState::Death:
			Death();
			break;
		}
	}
	void SCRIPT_SkelKnight::OnCollisionEnter(Collider2D* other)
	{
	}
	void SCRIPT_SkelKnight::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_SkelKnight::OnCollisionExit(Collider2D* other)
	{
	}
	void SCRIPT_SkelKnight::Spawn()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(spawn), false, mDirection);
		if (mOwner->GetComp<Animator>()->GetActiveAni()->IsComplete())
			mFSMState = eFSMState::Idle;
	}
	void SCRIPT_SkelKnight::Idle()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(idle), true, mDirection);
		//mAttacked = false;
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
	void SCRIPT_SkelKnight::Move()
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

		if (distance <= mOwner->GetStat().mRange * 2.0f)
			mFSMState = eFSMState::Attack;
	}
	void SCRIPT_SkelKnight::Attack()
	{
		if (GetDistance() > mOwner->GetStat().mRange * 2.0f)
			mFSMState = eFSMState::Move;

		SelectAttack();

		//Vector3 pos = mTarget->GetComp<Transform>()->GetPosition();

		mTime += Time::DeltaTime();

		Animator* at = mOwner->GetComp<Animator>();
		int index = at->GetActiveAni()->GetAniIndex();

		if (mAttackNum == 0) // orb 6번 뿌리기
		{
			mTime2 += Time::DeltaTime();

			if (mTime >= mOwner->GetStat().mCooldown)
			{
				mFireOrbNum = 0;
				mLaunched = false;
				at->PlayAnimation(AnimationName(attack), false, mDirection);
				mTime = 0.0f;
			}
			if (index > 5 
				&& index < 10
				&& at->GetActiveAni()->GetKey() == AnimationName(attack)
				&& mLaunched == false)
			{
				if (mTime2 >= 0.2f)
				{
					object::Instantiate<Bullet_FireOrb>(mOwner, eLayerType::Monster_Bullet, SceneManager::GetActiveScene());
					mTime2 = 0.0f;
					mFireOrbNum++;
				}
				if (mFireOrbNum >= 6)
				{
					mLaunched = true;
				}
			}
		}
		else if (mAttackNum == 1)
		{
			mTime2 += Time::DeltaTime();

			if (mTime >= mOwner->GetStat().mCooldown)
			{
				at->PlayAnimation(AnimationName(attack2), false, mDirection);
				mTime = 0.0f;
				mLaunched = false;
			}
			if (mLaunched == false)
			{
				mLaunched = true;
				if (mTime2 >= 0.2f)
				{
					object::Instantiate<Bullet_SKGroundFires>(mOwner, eLayerType::Monster_Bullet, SceneManager::GetActiveScene());
					mTime2 = 0.0f;
				}
			}
				//attack_groundfire();
		}
		//else if (mAttackNum == 2)
		//{
		//	if (mTime >= mOwner->GetStat().mCooldown)
		//	{
		//		at->PlayAnimation(AnimationName(attack3), false, mDirection);
		//		mTime = 0.0f;
		//	}
		//}
		//else if (mAttackNum == 3)
		//{
		//	if (mTime >= mOwner->GetStat().mCooldown)
		//	{
		//		at->PlayAnimation(AnimationName(attack4), false, mDirection);
		//		mTime = 0.0f;
		//	}
		//}

		if (mLaunched && at->GetActiveAni()->IsComplete())
		{
			at->PlayAnimation(AnimationName(idle), true, mDirection);
			mFSMState = eFSMState::Idle;
		}
	}
	void SCRIPT_SkelKnight::Attacked()
	{
	}
	void SCRIPT_SkelKnight::Death()
	{
	}
	std::wstring SCRIPT_SkelKnight::AnimationName(const std::wstring& animation)
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
	float SCRIPT_SkelKnight::GetDistance()
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		return (ppos - pos).Length();
	}
	Vector3 SCRIPT_SkelKnight::GetDirection()
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		return ppos - pos;
	}
	void SCRIPT_SkelKnight::SelectAttack()
	{
		std::random_device rd;  // 랜덤 시드를 얻기 위한 장치
		std::mt19937 gen(rd());  // 메르센 트위스터 난수 생성기 초기화
		std::uniform_int_distribution<> dist(0, 1);  // 0과 1 사이의 균등 분포

		mAttackNum = dist(gen);
	}
	void SCRIPT_SkelKnight::attack_shootorbs()
	{

	}
	void SCRIPT_SkelKnight::attack_groundfire()
	{

	}
	void SCRIPT_SkelKnight::attack_jump()
	{
	}
	void SCRIPT_SkelKnight::attack_shootorbssorted()
	{
	}
}
