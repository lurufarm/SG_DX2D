#include "SCRIPT_OldEnt.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Monster_Ranged.h"
#include "Gobj_Player.h"
#include "Gobj_Character.h"
#include "Gobj_Bullet.h"

#include <random>

#include "Effect_ProjectileDest.h"
#include "Effect_ProjectileDest2.h"
#include "Effect_OldEntStem.h"
#include "Bullet_Apple.h"
#include "Bullet_SlicedApple.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	SCRIPT_OldEnt::SCRIPT_OldEnt()
		: mOwner(nullptr)
	{
	}
	SCRIPT_OldEnt::~SCRIPT_OldEnt()
	{
	}
	void SCRIPT_OldEnt::Initialize()
	{
		mOwner = (Monster_Ranged*)GetOwner();
		mTarget = Player;
		mFSMState = eFSMState::Spwan;
		mDirection = false;
		mDeath = false;
		mLaunched = false;
		mAttackNum = false;
		mTime = 0.0f;
		mTime2 = 0.0f;
	}
	void SCRIPT_OldEnt::Update()
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
		case sg::SCRIPT_OldEnt::eFSMState::Spwan:
			Spawn();
			break;
		case sg::SCRIPT_OldEnt::eFSMState::Idle:
			Idle();
			break;
		case sg::SCRIPT_OldEnt::eFSMState::Move:
			Move();
			break;
		case sg::SCRIPT_OldEnt::eFSMState::Attack:
			Attack();
			break;
		case sg::SCRIPT_OldEnt::eFSMState::Attacked:
			Attacked();
			break;
		case sg::SCRIPT_OldEnt::eFSMState::Death:
			Death();
			break;
		}
	}

	void SCRIPT_OldEnt::OnCollisionEnter(Collider2D* other)
	{
		Gobj_Bullet* bullet = dynamic_cast<Gobj_Bullet*>(other->GetOwner());

		if (other->GetOwner() == bullet)
		{
			if (mAttacked == false)
			{
				mFSMState = eFSMState::Attacked;
				int hp = mOwner->GetStat().mCurHP;
				Gobj_Character::CharStat pStat = bullet->GetBulletOwner()->GetStat();
				hp -= (pStat.mStrength * pStat.mDamageScaling) - (pStat.mStrength * mOwner->GetStat().mDefence);
				mOwner->SetStatHP(hp);
			}
		}
	}
	void SCRIPT_OldEnt::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_OldEnt::OnCollisionExit(Collider2D* other)
	{
		if (other->GetOwner() == dynamic_cast<Gobj_Bullet*>(other->GetOwner()))
		{
			mAttacked = false;
		}
	}
	void SCRIPT_OldEnt::Spawn()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(spawn), false, mDirection);
		if (mOwner->GetComp<Animator>()->GetActiveAni()->IsComplete())
			mFSMState = eFSMState::Idle;
	}
	void SCRIPT_OldEnt::Idle()
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
	void SCRIPT_OldEnt::Move()
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
	void SCRIPT_OldEnt::Attack()
	{
		if (GetDistance() > mOwner->GetStat().mRange)
			mFSMState = eFSMState::Move;
		int stemnum = 0;

		SelectAttack();

		Vector3 pos = mTarget->GetComp<Transform>()->GetPosition();

		mTime += Time::DeltaTime();

		Animator* at = mOwner->GetComp<Animator>();

		if (mAttackNum == 0) // 사과 던지기 공격일 때
		{
			if (mTime >= mOwner->GetStat().mCooldown)
			{
				at->PlayAnimation(AnimationName(attack), false, mDirection);
				mTime = 0.0f;
			}

			if (at->GetActiveAni()->GetAniIndex() == 6
				&& at->GetActiveAni()->GetKey() == AnimationName(attack)
				&& mLaunched == false)
			{
				pos.z += 0.1f;
				Effect_ProjectileDest* epd = object::Instantiate<Effect_ProjectileDest>(pos, eLayerType::Effect, SceneManager::GetActiveScene());
				Bullet_Apple* app = object::Instantiate<Bullet_Apple>(mOwner, eLayerType::Monster_Bullet, SceneManager::GetActiveScene());
				mLaunched = true;
			}
		}
		else
		{
			mTime2 += Time::DeltaTime();
			std::map<int, Vector3> stempos = {};

			if (mTime >= mOwner->GetStat().mCooldown)
			{
				at->PlayAnimation(AnimationName(attack2), false, mDirection);
				mTime = 0.0f;
				mLaunched = false;
				stemnum = 0;
			}

			if (at->GetActiveAni()->GetAniIndex() > 4 
				&& at->GetActiveAni()->GetAniIndex() < 13
				&& at->GetActiveAni()->GetKey() == AnimationName(attack2)
				&& mLaunched == false)
			{
				if (mTime2 >= 0.1f)
				{
					Vector3 destPos = StemPos(pos);
					Effect_ProjectileDest2* epd = object::Instantiate<Effect_ProjectileDest2>(destPos, eLayerType::Effect, SceneManager::GetActiveScene());

					mTime2 = 0.0f;
					stemnum++;
				}
				if (stemnum >= 5)
				{
					mLaunched = true;
				}
			}
		}
		if (mLaunched && at->GetActiveAni()->IsComplete())
		{
			at->PlayAnimation(AnimationName(idle), true, mDirection);
			mFSMState = eFSMState::Idle;
		}
	}
	void SCRIPT_OldEnt::Attacked()
	{
		if (mAttacked == false)
		{
			mAttacked = true;
			mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(attacked), false, mDirection);
		}
		if (mOwner->GetComp<Animator>()->GetActiveAni()->IsComplete())
		{
			mFSMState = eFSMState::Idle;
		}
	}
	void SCRIPT_OldEnt::Death()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(death), false, mDirection);
		if (mOwner->GetComp<Animator>()->GetActiveAni()->IsComplete())
			mOwner->SetState(GameObject::eState::Dead);
	}
	std::wstring SCRIPT_OldEnt::AnimationName(const std::wstring& animation)
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
	float SCRIPT_OldEnt::GetDistance()
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		return (ppos - pos).Length();
	}
	Vector3 SCRIPT_OldEnt::GetDirection()
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		return ppos - pos;
	}
	void SCRIPT_OldEnt::SelectAttack()
	{
		std::random_device rd;  // 랜덤 시드를 얻기 위한 장치
		std::mt19937 gen(rd());  // 메르센 트위스터 난수 생성기 초기화
		std::uniform_int_distribution<> dist(0, 1);  // 0과 1 사이의 균등 분포

		mAttackNum = dist(gen);
	}
	Vector3 SCRIPT_OldEnt::StemPos(Vector3 pos)
	{
		static bool isSeeded = false;

		if (!isSeeded) {
			srand(static_cast<unsigned int>(time(nullptr)));
			isSeeded = true;
		}

		// random angle
		const float PI = 3.141592;
		float angle = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * 2 * PI);

		// random distance
		float distance = 50.0f;
		float randomDistance = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * distance);

		// angle + distance
		Vector3 randomPos;
		randomPos.x = pos.x + randomDistance * cos(angle);
		randomPos.y = pos.y + randomDistance * sin(angle);
		randomPos.z = pos.z + 0.01f;

		return randomPos;
	}
}