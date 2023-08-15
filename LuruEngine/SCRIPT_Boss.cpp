#include "SCRIPT_Boss.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Monster_Ranged.h"
#include "Gobj_Player.h"
#include "Gobj_Character.h"
#include "Gobj_Bullet.h"

#include <random>

#include "Effect_ProjectileDest.h"
#include "Bullet_Apple.h"
#include "Bullet_SlicedApple.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	SCRIPT_Boss::SCRIPT_Boss()
		: mOwner(nullptr)
	{
	}
	SCRIPT_Boss::~SCRIPT_Boss()
	{
	}
	void SCRIPT_Boss::Initialize()
	{
		mOwner = (Monster_Ranged*)GetOwner();
		mTarget = Player;
		mFSMState = eFSMState::Spwan;
		mDirection = false;
		mDeath = false;
		mLaunched = false;
		mAttackNum = false;
	}
	void SCRIPT_Boss::Update()
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();

		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		// 필수
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
		case sg::SCRIPT_Boss::eFSMState::Spwan:
			Spawn();
			break;
		case sg::SCRIPT_Boss::eFSMState::Idle:
			Idle();
			break;
		case sg::SCRIPT_Boss::eFSMState::Move:
			Move();
			break;
		case sg::SCRIPT_Boss::eFSMState::Attack:
			Attack();
			break;
		case sg::SCRIPT_Boss::eFSMState::Attacked:
			Attacked();
			break;
		case sg::SCRIPT_Boss::eFSMState::Death:
			Death();
			break;
		}
	}
	void SCRIPT_Boss::LateUpdate()
	{
	}
	void SCRIPT_Boss::Render()
	{
	}
	void SCRIPT_Boss::OnCollisionEnter(Collider2D* other)
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
	void SCRIPT_Boss::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_Boss::OnCollisionExit(Collider2D* other)
	{
		if (other->GetOwner() == dynamic_cast<Gobj_Bullet*>(other->GetOwner()))
		{
			mAttacked = false;
		}
	}
	void SCRIPT_Boss::Spawn()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(spawn), false, mDirection);
		if (mOwner->GetComp<Animator>()->GetActiveAni()->IsComplete())
			mFSMState = eFSMState::Idle;
	}
	void SCRIPT_Boss::Idle()
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
	void SCRIPT_Boss::Move()
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
	void SCRIPT_Boss::Attack()
	{
		if (GetDistance() > mOwner->GetStat().mRange)
			mFSMState = eFSMState::Move;
		SelectAttack();
		mTime += Time::DeltaTime();
		Animator* at = mOwner->GetComp<Animator>();

		if (mAttackNum == 0) // 사과 던지기 공격일 때
		{
			if (mTime >= mOwner->GetStat().mCoolDown)
			{
				at->PlayAnimation(AnimationName(attack), false, mDirection);
				mTime = 0.0f;
			}

			if (at->GetActiveAni()->GetAniIndex() == 6
				&& at->GetActiveAni()->GetKey() == AnimationName(attack)
				&& mLaunched == false)
			{
				Vector3 pos = mTarget->GetComp<Transform>()->GetPosition();
				pos.z += 0.1f;
				Effect_ProjectileDest* epd = object::Instantiate<Effect_ProjectileDest>(pos, eLayerType::Effect, SceneManager::GetActiveScene());
				Bullet_Apple* app = object::Instantiate<Bullet_Apple>(mOwner, eLayerType::Monster_Bullet, SceneManager::GetActiveScene());
				mLaunched = true;
			}
		}
		if (mLaunched && at->GetActiveAni()->IsComplete())
		{
			at->PlayAnimation(AnimationName(idle), true, mDirection);
			mFSMState = eFSMState::Idle;
		}
	}
	void SCRIPT_Boss::Attacked()
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
	void SCRIPT_Boss::Death()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(death), false, mDirection);
		if (mOwner->GetComp<Animator>()->GetActiveAni()->IsComplete())
			mOwner->SetState(GameObject::eState::Dead);
	}
	std::wstring SCRIPT_Boss::AnimationName(const std::wstring& animation)
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
	float SCRIPT_Boss::GetDistance()
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		return (ppos - pos).Length();
	}
	Vector3 SCRIPT_Boss::GetDirection()
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		return ppos - pos;
	}
	void SCRIPT_Boss::SelectAttack()
	{
		std::random_device rd;  // 랜덤 시드를 얻기 위한 장치
		std::mt19937 gen(rd());  // 메르센 트위스터 난수 생성기 초기화
		std::uniform_int_distribution<> dist(0, 1);  // 0과 1 사이의 균등 분포

		mAttackNum = dist(gen);
	}
}