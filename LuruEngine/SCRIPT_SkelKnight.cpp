#include "SCRIPT_SkelKnight.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Gobj_Player.h"
#include "Bullet_FireOrb.h"
#include "Bullet_FireOrbs.h"
#include "Bullet_SKGroundFires.h"
#include "Img_Shadow.h"
#include "Effect_BigDust.h"
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
		mShadow = nullptr;
	}
	void SCRIPT_SkelKnight::Update()
	{
		Transform* tr = mOwner->GetComp<Transform>();
		Transform* ptr = mTarget->GetComp<Transform>();

		Vector3 pos = tr->GetPosition();
		Vector3 ppos = ptr->GetPosition();

		if (mShadow == nullptr)
			mShadow = object::Instantiate<Img_Shadow>(mOwner->GetComp<Transform>()->GetPosition(), eLayerType::BGImg, SceneManager::GetActiveScene());

		Vector3 shadowpos = pos;
		shadowpos.y -= 35.0f;
		mShadow->GetComp<Transform>()->SetPosition(shadowpos);

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
		Gobj_Bullet* bullet = dynamic_cast<Gobj_Bullet*>(other->GetOwner());

		if (other->GetOwner() == bullet)
		{
			int hp = mOwner->GetStat().mCurHP;
			Gobj_Character::CharStat pStat = bullet->GetBulletOwner()->GetStat();
			hp -= (pStat.mStrength * pStat.mDamageScaling) - (pStat.mStrength * mOwner->GetStat().mDefence);
			mOwner->SetStatHP(hp);
		}
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
		mAttackable = false;
	}
	void SCRIPT_SkelKnight::Idle()
	{
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(idle), true, mDirection);
		mLaunched = false;
		mAttackable = false;

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
		mAttackable = false;
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(move), true, mDirection);

		Transform* tr = mOwner->GetComp<Transform>();
		Vector3 pos = tr->GetPosition();

		float distanceToMove = mOwner->GetStat().mSpeed * 1.3f * Time::DeltaTime();
		Vector3 direction = GetDirection();
		direction.Normalize();
		pos += direction * distanceToMove;
		tr->SetPosition(pos);

		if (GetDistance() < mOwner->GetStat().mRange)
			mFSMState = eFSMState::Attack;
	}
	void SCRIPT_SkelKnight::Attack()
	{
		mAttackable = false;
		if (GetDistance() >= mOwner->GetStat().mRange)
			mFSMState = eFSMState::Move;
		SelectAttack();
		mTime += Time::DeltaTime();
		Animator* at = mOwner->GetComp<Animator>();
		int index = at->GetActiveAni()->GetAniIndex();

		if (mAttackNum == 0) // orb 무작위로 뿌리기
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
				if (mTime2 >= 0.02f)
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
			if (mTime >= mOwner->GetStat().mCooldown)
			{
				at->PlayAnimation(AnimationName(attack2), false, mDirection);
				mTime = 0.0f;
				mLaunched = false;
			}
			if (mLaunched == false)
			{
				if (index == 5
					&& at->GetActiveAni()->GetKey() == AnimationName(attack2))
				{
					mLaunched = true;
					object::Instantiate<Bullet_SKGroundFires>(mOwner, eLayerType::Monster_Bullet, SceneManager::GetActiveScene());
				}
			}
		}
		else if (mAttackNum == 2) // 점프
		{
			if (mTime >= mOwner->GetStat().mCooldown)
			{
				mAttack3TargetPos = mTarget->GetComp<Transform>()->GetPosition();
				mAttack3OwnerPos = mOwner->GetComp<Transform>()->GetPosition();
				at->PlayAnimation(AnimationName(attack3), false, mDirection);
				mTime = 0.0f;
				mTime2 = 0.0f;
			}
			Vector3 skpos = mOwner->GetComp<Transform>()->GetPosition();
			if (mLaunched == false
				&& index > 4
				&& index < 13
				&& at->GetActiveAni()->GetKey() == AnimationName(attack3))
			{
				mTime2 += Time::DeltaTime();
				float curveHeight = 40.0f;
				float curveDuration = 0.8f; 
				float t2 = min(mTime2 / curveDuration, 1.0f);

				float xDist = mAttack3TargetPos.x - mAttack3OwnerPos.x;
				float yDist = mAttack3TargetPos.y - mAttack3OwnerPos.y + 20.0f;

				float x = mAttack3OwnerPos.x + xDist * t2;
				float y = mAttack3OwnerPos.y + yDist * t2 + curveHeight * (4.0f * t2 * (1.0f - t2));
				float z = -1.0f;

				skpos = Vector3(x, y, z);
				mOwner->GetComp<Transform>()->SetPosition(skpos);

				if (GetDistance() <= 20.0f) 
				{
					mAttackable = true;
					mTime2 = 0.0f;
					mLaunched = true;
					Vector3 dustpos = skpos;
					dustpos.y -= 15.0f;
					object::Instantiate<Effect_BigDust>(dustpos, eLayerType::Monster_Effect, SceneManager::GetActiveScene());
				}
			}
		}
		else if (mAttackNum == 3)
		{
			mTime2 += Time::DeltaTime();
			if (mTime >= mOwner->GetStat().mCooldown)
			{
				mFireOrbNum = 0;
				mLaunched = false;
				at->PlayAnimation(AnimationName(attack4), false, mDirection);
				mTime = 0.0f;
			}
			if (index > 5
				&& index < 16
				&& at->GetActiveAni()->GetKey() == AnimationName(attack4)
				&& mLaunched == false)
			{
				if (mFireOrbNum > 4)
				{
					mTime2 = 0.0f;
					mLaunched = true;
				}
				if (mTime2 >= 0.3f)
				{
					mTime2 = 0.0f;
					mFireOrbNum++;
					object::Instantiate<Bullet_FireOrbs>(mOwner, eLayerType::Monster_Bullet, SceneManager::GetActiveScene());
				}
			}
		}
	}
	void SCRIPT_SkelKnight::Attacked()
	{
	}
	void SCRIPT_SkelKnight::Death()
	{
		mAttackable = false;
		mOwner->GetComp<Animator>()->PlayAnimation(AnimationName(death), false, mDirection);
		if (mOwner->GetComp<Animator>()->GetActiveAni()->IsComplete())
		{
			mOwner->SetState(GameObject::eState::Dead);
			mShadow->SetState(GameObject::eState::Dead);
		}
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
		std::uniform_int_distribution<> dist(0, 3); // 0 ~ 3 랜덤

		mAttackNum = dist(gen);
	}
}
