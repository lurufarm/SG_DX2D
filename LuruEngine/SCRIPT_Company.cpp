#include "SCRIPT_Company.h"
#include <random>

#include "..\Engine_SOURCE\sgSceneManager.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "SCENE_PlayScene.h"
#include "Gobj_Player.h"
#include "Bullet_CheeseArrow.h"
#include "Bullet_LucyBomb.h"
#include "Bullet_RoboBeam.h"
#include "Bullet_SzilaFire.h"
#include "Effect_LaserFiring.h"
#include "UI_StatusBase.h"

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

		//mPlayer = Player;
		mOwner = (Gobj_Character*)GetOwner();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObj(eLayerType::Player, mOwner);
		PlayScene* playsc = dynamic_cast<PlayScene*>(scene);
		playsc->CreateCompanyLight(mOwner);
		Player->AddCompany(mOwner);
		mPtr = Player->GetComp<Transform>();
		mOtr = mOwner->GetComp<Transform>();
		mOat = mOwner->GetComp<Animator>();
		mOcol = mOwner->AddComp<Collider2D>();
		mOcol->SetSize(Vector2(0.4f, 0.7f));
		IsEnemyNear = false;
		Vector3 ppos = mPtr->GetPosition();
		mOtr->SetPosition(RandPos(ppos));
		mTarget = nullptr;
		mOat->PlayAnimation(AnimationName(idle), true, true);
		mTime = 0.0f;
	}
	void SCRIPT_Company::Update()
	{
		if (mPlayer->GetStat().mCurHP <= 0)
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
			if (distanceOfMob.begin()->first <= mOwner->GetStat().mRange * 2.0f)
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
		case sg::SCRIPT_Company::eCompanyFSM::Move2:
			Move2();
			break;
		case sg::SCRIPT_Company::eCompanyFSM::Attack:
			Attack();
			break;
		case sg::SCRIPT_Company::eCompanyFSM::Death:
			Death();
			break;
		}
	}
	void SCRIPT_Company::OnCollisionEnter(Collider2D* other)
	{
		Gobj_Character* company = dynamic_cast<Gobj_Character*>(other->GetOwner());
		if (company == other->GetOwner() || Player == other->GetOwner())
		{
			eCompanyFSM prefsm = mFSMState;
			mFSMState = eCompanyFSM::Move2;
			if (prefsm != mFSMState)
			{
				mRandomDirection = OppositeDirection(other->GetOwner()->GetComp<Transform>()->GetPosition());
			}
		}
	}
	void SCRIPT_Company::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_Company::OnCollisionExit(Collider2D* other)
	{
		if (IsEnemyNear)
			mFSMState = eCompanyFSM::Attack;
		else
			mFSMState = eCompanyFSM::Idle;
	}
	void SCRIPT_Company::Idle()
	{
		mTime += Time::DeltaTime();

		mOat->PlayAnimation(AnimationName(idle), true, mDirection);
		
		if (GetDistanceToPlayer() >= 50.0f)
		{
			mFSMState = eCompanyFSM::Move;
			mTime = 0.0f;
		}
		if (IsEnemyNear)
			mFSMState = eCompanyFSM::Attack;

		if (mTime >= 5.0f)
		{
			mRandomDirection = RandomDirection();
			mFSMState = eCompanyFSM::Move2;
			mTime = 0.0f;
		}

	}
	void SCRIPT_Company::Move()
	{
		mTime += Time::DeltaTime();

		if (GetDirectionToPlayer().x < 0)
			mDirection = false;
		else
			mDirection = true;

		mOat->PlayAnimation(AnimationName(move), true, mDirection);

		if (GetDistanceToPlayer() < 50.0f && mTime >= 1.0f)
		{
			mFSMState = eCompanyFSM::Idle;
			mTime = 0.0f;
		}
		
		Vector3 pos = mOtr->GetPosition();
		pos += GetDirectionToPlayer() * mOwner->GetStat().mSpeed * Time::DeltaTime();
		mOtr->SetPosition(pos);

	}
	void SCRIPT_Company::Move2()
	{
		if (mRandomDirection.x < 0)
			mDirection = false;
		else
			mDirection = true;

		//if (GetDistanceToPlayer() < 30.0f)
		//	mFSMState = eCompanyFSM::Idle;
		
		if (GetDistanceToPlayer() >= 80.0f)
			mFSMState = eCompanyFSM::Move;

		mOat->PlayAnimation(AnimationName(move), true, mDirection);

		Vector3 pos = mOtr->GetPosition();
		pos += mRandomDirection * mOwner->GetStat().mSpeed * Time::DeltaTime();
		mOtr->SetPosition(pos);
	}
	void SCRIPT_Company::Attack()
	{
		mTime += Time::DeltaTime();

		if (IsEnemyNear == false)
			mFSMState = eCompanyFSM::Idle;
		if (GetDistanceToPlayer() >= 80.0f)
			mFSMState = eCompanyFSM::Move;

		if (mTime >= mOwner->GetStat().mCooldown && mOwner->GetStat().mRange * 2.0f >= GetDistanceToOther())
		{
			mOat->PlayAnimation(AnimationName(attack), false, mDirection);
			if (mOwner->GetName() == L"Cheese")
			{
				for (size_t i = 1; i <= mOwner->GetStat().mProjectileCount; i++)
				{
					object::ShootBullet<Bullet_CheeseArrow>(i, eLayerType::Player_Bullet, SceneManager::GetActiveScene());
				}
			}
			else if (mOwner->GetName() == L"Lucy")
			{
				for (size_t i = 1; i <= mOwner->GetStat().mProjectileCount; i++)
				{
					object::ShootBullet<Bullet_LucyBomb>(i, eLayerType::Player_Bullet, SceneManager::GetActiveScene());
				}
			}
			else if (mOwner->GetName() == L"Robo")
			{
				int RoboBeamRange = (int)(mOwner->GetStat().mRange - 100.0f) / 100.0f;
				Vector3 epos = mOwner->GetComp<Transform>()->GetPosition();
				epos.z -= 2.0f;
				object::Instantiate<Effect_LaserFiring>(epos, eLayerType::Player_Effect, SceneManager::GetActiveScene());
				object::ShootBullet<Bullet_RoboBeam>(RoboBeamRange, eLayerType::Player_Beam, SceneManager::GetActiveScene());
			}
			else if (mOwner->GetName() == L"Szila")
			{
				object::ShootBullet<Bullet_SzilaFire>(mOwner->GetStat().mProjectileCount, eLayerType::Player_Bullet, SceneManager::GetActiveScene());
			}
			mTime = 0.0f;
		}

		if (mOat->GetActiveAni()->IsComplete() && mOat->GetActiveAni()->GetKey() == AnimationName(attack))
		{
			mFSMState = eCompanyFSM::Idle;
			mOat->PlayAnimation(AnimationName(idle), true, mDirection);
			mTime = 0.0f;
		}

	}
	void SCRIPT_Company::Death()
	{
		mTime = 0.0f;
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
	Vector3 SCRIPT_Company::RandomDirection()
	{
		std::random_device rd;  // 랜덤한 시드 생성
		std::mt19937 gen(rd()); // Mersenne Twister 알고리즘을 사용하는 난수 생성기
		std::uniform_real_distribution<> dis(-1.0, 1.0);  // -1부터 1까지의 균일 분포

		float x = dis(gen);
		float y = dis(gen);

		Vector3 direction = Vector3(x, y, 0.0f);
		direction.Normalize();

		return direction;
	}
	Vector3 SCRIPT_Company::OppositeDirection(Vector3 pos)
	{
		Vector3 mypos = mOwner->GetComp<Transform>()->GetPosition();
		mypos -= pos;
		mypos.Normalize();

		return mypos;
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