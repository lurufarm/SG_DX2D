#include "SCRIPT_Company.h"
#include <random>

#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Gobj_Player.h"
#include "Bullet_CheeseArrow.h"
#include "Bullet_LucyBomb.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	SCRIPT_Company::SCRIPT_Company()
	{

	}
	SCRIPT_Company::~SCRIPT_Company()
	{
	}
	void SCRIPT_Company::Initialize()
	{
		mPlayer = Player;
		mOwner = (Gobj_Character*)GetOwner();

		mPtr = mPlayer->GetComp<Transform>();
		mOtr = mOwner->GetComp<Transform>();
		mOat = mOwner->GetComp<Animator>();
		IsEnemyNear = false;
		Vector3 ppos = mPtr->GetPosition();
		mOtr->SetPosition(RandPos(ppos));
		mTarget = nullptr;
		mOat->PlayAnimation(AnimationName(idle), true, true);
		mTime = 0.0f;
	}
	void SCRIPT_Company::Update()
	{
		if (mPlayer->GetStat().mHP <= 0)
		{
			mDeath = true;
			mFSMState = eCompanyFSM::Death;
		}
		
		std::vector<GameObject*> monsters = SceneManager::GetActiveScene()->GetLayer(eLayerType::Monster).GetGameObjects();
		std::map<float, GameObject*> distanceOfMob;
		Vector3 ownerpos = mOtr->GetPosition();

		if (monsters.size() > 0)
		{
			for (GameObject* mob : monsters)
			{
				Vector3 mobpos = mob->GetComp<Transform>()->GetPosition();

				float distance = sqrt(pow(mobpos.x - ownerpos.x, 2)
					+ pow(mobpos.y - ownerpos.y, 2));

				distanceOfMob.insert(std::make_pair(distance, mob));
			}
			mTarget = distanceOfMob.begin()->second;
			if (distanceOfMob.begin()->first <= mOwner->GetStat().mRange)
			{
				IsEnemyNear = true;
				if (mTarget->GetComp<Transform>()->GetPosition().x >
					mOtr->GetPosition().x)
					mDirection = true;
				else
					mDirection = false;
			}
			else
				IsEnemyNear = false;
		}
		else
			IsEnemyNear = false;

		switch (mFSMState)
		{
		case sg::SCRIPT_Company::eCompanyFSM::Idle:
			Idle();
			break;
		case sg::SCRIPT_Company::eCompanyFSM::Move:
			Move();
			break;
		case sg::SCRIPT_Company::eCompanyFSM::Attack:
			Attack();
			break;
		case sg::SCRIPT_Company::eCompanyFSM::Death:
			Death();
			break;
		}
	}
	void SCRIPT_Company::Idle()
	{
		mOat->PlayAnimation(AnimationName(idle), true, mDirection);

		if (IsEnemyNear)
			mFSMState = eCompanyFSM::Attack;
		
		if (GetDistanceToPlayer() >= 50.0f)
			mFSMState = eCompanyFSM::Move;

	}
	void SCRIPT_Company::Move()
	{
		if (mOtr->GetPosition().x >= mPtr->GetPosition().x)
			mDirection = false;
		else
			mDirection = true;

		if (GetDistanceToPlayer() < 50.0f)
			mFSMState = eCompanyFSM::Idle;
		
		mOat->PlayAnimation(AnimationName(move), true, mDirection);

		Vector3 pos = mOtr->GetPosition();
		pos += GetDirectionToPlayer() * mOwner->GetStat().mSpeed * Time::DeltaTime();
		mOtr->SetPosition(pos);

	}
	void SCRIPT_Company::Attack()
	{
		mTime += Time::DeltaTime();

		if (IsEnemyNear == false)
			mFSMState = eCompanyFSM::Idle;
		if (GetDistanceToPlayer() >= 80.0f)
			mFSMState = eCompanyFSM::Move;

		//mOat->PlayAnimation(AnimationName(attack), false, mDirection);

		if (mTime >= mOwner->GetStat().mCoolDown)
		{
			mOat->PlayAnimation(AnimationName(attack), false, mDirection);
			if (mOwner->GetName() == L"Cheese")
				object::Instantiate<Bullet_CheeseArrow>(eLayerType::Player_Bullet, SceneManager::GetActiveScene());
			else if (mOwner->GetName() == L"Lucy")
				object::Instantiate<Bullet_LucyBomb>(eLayerType::Player_Bullet, SceneManager::GetActiveScene());
			mTime = 0.0f;
		}

		if (mOat->GetActiveAni()->IsComplete() && mOat->GetActiveAni()->GetKey() == AnimationName(attack))
		{
			mFSMState = eCompanyFSM::Idle;
			mOat->PlayAnimation(AnimationName(idle), true, mDirection);
		}

	}
	void SCRIPT_Company::Death()
	{
		mOat->PlayAnimation(AnimationName(death), false, mDirection);
	}

	Vector3 SCRIPT_Company::RandPos(Vector3 pos)
	{
		const float PI = 3.141592;
		float angle = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * 2 * PI);

		// random distance
		float distance = 30.0f;
		float randomDistance = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * distance);

		// angle + distance
		Vector3 randomPos;
		randomPos.x = pos.x + randomDistance * cos(angle);
		randomPos.y = pos.y + randomDistance * sin(angle);
		randomPos.z = pos.z;

		return randomPos;
	}
	std::wstring SCRIPT_Company::AnimationName(const std::wstring& animation)
	{
		std::wstring animationName = L"Ani_";
		animationName += mOwner->GetName();
		animationName += L"_";
		animationName += animation;
		return animationName;
	}
}