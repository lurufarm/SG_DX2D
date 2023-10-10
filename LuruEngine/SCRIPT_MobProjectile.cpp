#include "SCRIPT_MobProjectile.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Gobj_Character.h"
#include "Gobj_Player.h"

#include "Bullet_SlicedApple.h"
#include "Effect_Hit.h"
#include "Effect_Explosion.h"
#include "Effect_FirePlate.h"
#include "Effect_FirePlate2.h"
#include "Effect_ProjectileDest.h"
#include "Effect_RockDust.h"
#include "Effect_DustExplosion.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	void SCRIPT_MobProjectile::Initialize()
	{
		mTime = 0.0f;
		mProj = (Gobj_MobProjectile*)GetOwner();
		mProjOwner = mProj->GetProjOwner();
		mProjType = mProj->GetProjType();
		mTarget = Player;
		if (mProjOwner != nullptr)
		{
			mFirstPos = mProjOwner->GetComp<Transform>()->GetPosition();
			mLastPos = mTarget->GetComp<Transform>()->GetPosition();
			mTotalDuration = Time::DeltaTime() * 2;

			if (mProjType == eMProjType::Basic_RandDir)
			{
				mLastPos = mTarget->GetComp<Transform>()->GetPosition();
				LastPos_RandomDir(30.0f);
				mTotalDuration = GetDistance() / 1000.0f;
			}
			else if (mProjType == eMProjType::Basic_NearCardinalDir)
			{
				mLastPos = mProj->GetLastPos();
				mTotalDuration = GetDistance() / 20.0f;
				mLastPos += mFirstPos;
			}
			else if (mProjType == eMProjType::Basic_Dir)
			{
				mFirstPos = mProj->GetFirstPos();
				mLastPos = mProj->GetLastPos();
				mTotalDuration = Time::DeltaTime() * 2;
				mLastPos += mFirstPos;
			}
			else if (mProjType == eMProjType::Fire)
			{
				mFirstPos = mProj->GetFirstPos();
				mLastPos = mFirstPos;
				mTotalDuration = 0;
			}
			else if (mProjType == eMProjType::WhirlWind)
			{
				mLastPos = mTarget->GetComp<Transform>()->GetPosition();
				LastPos_RandomDir(50.0f);
				mTotalDuration = Time::DeltaTime();
			}
			else if (mProjType == eMProjType::BloodSpit)
			{
				mFirstPos.y -= 5.0f;
				mLastPos = mProj->GetLastPos();
				Vector2 direction = GetDirection();
				float angleDegree = sgGetAngle(direction) - 90.0f;
				Transform* tr = mProj->GetComp<Transform>();
				tr->SetRotation(Vector3(0.0f, 0.0f, angleDegree));
			}
		}
		else
		{
			mFirstPos = mProj->GetFirstPos();
			mLastPos = mProj->GetLastPos();
			mTotalDuration = GetDistance() / 100.0f;
		}

		IsLaunched = false;
		IsActivated = false;

	}
	void SCRIPT_MobProjectile::Update()
	{
		mTime += Time::DeltaTime();
		float t = mTime / mTotalDuration;
		Vector3 curPos;
		Vector2 curDir = GetDirection();

		if (mProjType == eMProjType::PoisonOrb)
		{
			float speed = GetSpeed() * mTotalDuration * 7.0f;
			IsActivated = true;
			// Set the amplitude of the sine wave
			float amplitude = 5.0f;
			// Set the frequency of the sine wave
			float frequency = 15.0f;

			// Calculate the new position
			curPos.x = mFirstPos.x + curDir.x * t * speed - (sin(t * frequency) * amplitude * curDir.y);
			curPos.y = mFirstPos.y + curDir.y * t * speed + (sin(t * frequency) * amplitude * curDir.x);
			curPos.z = -1.0f;
			mProj->GetComp<Transform>()->SetPosition(curPos);
		}
		else if (mProjType == eMProjType::LightningOrb)
		{
			float speed = GetSpeed() * mTotalDuration * 7.0f;
			IsActivated = true;
			// Set the amplitude of the sine wave
			float amplitude = 10.0f;
			// Set the frequency of the sine wave
			float frequency = 0.1f;

			// Calculate the new position
			curPos.x = mFirstPos.x + curDir.x * t * speed - (sin(t * frequency) * amplitude * curDir.y);
			curPos.y = mFirstPos.y + curDir.y * t * speed + (sin(t * frequency) * amplitude * curDir.x);
			curPos.z = -1.0f;
			mProj->GetComp<Transform>()->SetPosition(curPos);
		}
		else if (mProjType == eMProjType::WhirlWind)
		{
			float speed = GetSpeed() * mTotalDuration * 1.5f;
			IsActivated = true;
			// Set the amplitude of the sine wave
			float amplitude = 20.0f;
			// Set the frequency of the sine wave
			float frequency = 0.05f;

			// Calculate the new position
			curPos.x = mFirstPos.x + curDir.x * t * speed - (sin(t * frequency) * amplitude * curDir.y);
			curPos.y = mFirstPos.y + curDir.y * t * speed + (sin(t * frequency) * amplitude * curDir.x);
			curPos.z = -1.0f;

			mProj->GetComp<Transform>()->SetPosition(curPos);
		}
		else if (mProjType == eMProjType::EntRock)
		{
			float curveHeight = 30.0f; // ��� ����
			float curveDuration = 1.0f; // � � �ð�

			// �ð��� ��ȭ���� ���
			float t2 = mTime / curveDuration;

			// ������ ��� �������� x, y, z ��ǥ ���
			float xDist = mLastPos.x - mFirstPos.x; // x ��ǥ�� �̵� �Ÿ�
			float yDist = mLastPos.y - mFirstPos.y; // y ��ǥ�� �̵� �Ÿ�
			float x = mFirstPos.x + t2 * xDist;
			float y = mFirstPos.y + t2 * yDist + curveHeight * 4.0f * t2 * (1.0f - t2);
			float z = -1.0f;
			curPos = Vector3(x, y, z);
			mProj->GetComp<Transform>()->SetPosition(curPos);

			if (GetDistance() <= 30.0f)
				IsActivated = true;
		}
		else if (mProjType == eMProjType::MummyBomb)
		{
			float curveHeight = 30.0f; // ��� ����
			float curveDuration = 1.0f; // � � �ð�

			// �ð��� ��ȭ���� ���
			float t2 = mTime / curveDuration;

			// ������ ��� �������� x, y, z ��ǥ ���
			float xDist = mLastPos.x - mFirstPos.x; // x ��ǥ�� �̵� �Ÿ�
			float yDist = mLastPos.y - mFirstPos.y; // y ��ǥ�� �̵� �Ÿ�
			float x = mFirstPos.x + t2 * xDist;
			float y = mFirstPos.y + t2 * yDist + curveHeight * 4.0f * t2 * (1.0f - t2);
			float z = -1.0f;
			curPos = Vector3(x, y, z);
			mProj->GetComp<Transform>()->SetPosition(curPos);

			if (GetDistance() <= 30.0f)
				IsActivated = true;
			if (GetDistance() <= 5.0f)
			{
				object::Instantiate<Effect_Explosion>(curPos, eLayerType::Effect, SceneManager::GetActiveScene());
				object::Instantiate<Effect_FirePlate2>(Vector3(curPos.x, curPos.y, curPos.z + 0.1f), eLayerType::Monster_Effect, SceneManager::GetActiveScene());
				mProj->SetState(GameObject::eState::Dead);
			}
		}
		else if (mProjType == eMProjType::Spear)
		{
			float curveHeight = 30.0f; // ��� ����
			float curveDuration = 1.0f; // � � �ð�

			// �ð��� ��ȭ���� ���
			float t2 = mTime / curveDuration;

			// ������ ��� �������� x, y, z ��ǥ ���
			float xDist = mLastPos.x - mFirstPos.x; // x ��ǥ�� �̵� �Ÿ�
			float yDist = mLastPos.y - mFirstPos.y; // y ��ǥ�� �̵� �Ÿ�
			float x = mFirstPos.x + t2 * xDist;
			float y = mFirstPos.y + t2 * yDist + curveHeight * 4.0f * t2 * (1.0f - t2);
			float z = -1.0f;
			curPos = Vector3(x, y, z);

			Vector3 direction = curPos - mFirstPos;
			direction.Normalize(); // ���� ���͸� ����ȭ
			float an = sgGetAngleInRadian(180.0f);
			float yaw = sgGetAngle(Vector2(direction.y, direction.x));
			
			mProj->GetComp<Transform>()->SetRotation(Vector3(0.0f, 0.0f, -yaw + an));
			mProj->GetComp<Transform>()->SetPosition(curPos);

			if (GetDistance() <= 30.0f)
				IsActivated = true;
			if (GetDistance() <= 5.0f)
			{
				mProj->SetState(GameObject::eState::Dead);
			}
		}
		else if (mProjType == eMProjType::BigOrb)
		{
			float curveHeight = 20.0f; // ��� ����
			float curveDuration = 2.0f; // � � �ð�

			// �ð��� ��ȭ���� ���
			float t2 = mTime / curveDuration;

			// ������ ��� �������� x, y, z ��ǥ ���
			float xDist = mLastPos.x - mFirstPos.x; // x ��ǥ�� �̵� �Ÿ�
			float yDist = mLastPos.y - mFirstPos.y; // y ��ǥ�� �̵� �Ÿ�
			float x = mFirstPos.x + t2 * xDist;
			float y = mFirstPos.y + t2 * yDist + curveHeight * 4.0f * t2 * (1.0f - t2);
			float z = -1.0f;
			curPos = Vector3(x, y, z);
			mProj->GetComp<Transform>()->SetPosition(curPos);

			if (GetDistance() <= 30.0f)
				IsActivated = true;
			if (GetDistance() <= 20.0f)
			{
				mProj->SetState(GameObject::eState::Dead);
			}
		}
		else if (mProjType == eMProjType::Fire)
			IsActivated = true;
		else if (mProjType == eMProjType::Basic 
			|| mProjType == eMProjType::Basic_RandDir 
			|| mProjType == eMProjType::Basic_NearCardinalDir
			|| mProjType == eMProjType::Basic_Dir
			|| mProjType == eMProjType::BloodSpit)
		{
			IsActivated = true;
			curPos = mFirstPos + (t * 5.0f)* GetDirection();
			curPos.z = -1.0f;
			mProj->GetComp<Transform>()->SetPosition(curPos);
		}

		 // �����Ÿ� �̻��� �Ǹ� �����
		//if (GetDistance() >= GetRange() * 2.0f)
		//{
		//	mProj->SetState(GameObject::eState::Dead);
		//}
	}
	void SCRIPT_MobProjectile::OnCollisionEnter(Collider2D* other)
	{
		Vector3 pos;

		if (mProjOwner != nullptr)
		{
			if (mProjOwner->GetName() == L"Ent")
			{
				if (other->GetOwner() != mTarget)
				{
					mProj->SetState(GameObject::eState::Dead);
					object::Instantiate<Effect_RockDust>(Vector3(mLastPos.x, mLastPos.y + 10.0f, mLastPos.z), eLayerType::Monster_Effect, SceneManager::GetActiveScene());
				}
			}
			else if (mProjOwner->GetName() == L"OldEnt" && IsLaunched == false)
			{
				//Vector3 test = Vector3(100.0f, 100.0f, -5.0f);
				pos = mProj->GetComp<Transform>()->GetPosition();
				object::SlicedApple(pos, 0);
				object::SlicedApple(pos, 1);
				object::SlicedApple(pos, 2);
				object::SlicedApple(pos, 3);
				object::Instantiate<Effect_RockDust>(Vector3(pos.x, pos.y + 10, pos.z - 1.0f), eLayerType::Effect, SceneManager::GetActiveScene());
				mProj->SetState(GameObject::eState::Dead);
			}
			else if (mProjOwner->GetName() == L"MummyBomb")
			{
				pos = mProj->GetComp<Transform>()->GetPosition();
				object::Instantiate<Effect_Explosion>(pos, eLayerType::Effect, SceneManager::GetActiveScene());
				object::Instantiate<Effect_FirePlate2>(Vector3(pos.x, pos.y, pos.z + 0.1f), eLayerType::Monster_Effect, SceneManager::GetActiveScene());
				mProj->SetState(GameObject::eState::Dead);

			}
			else if (mProjOwner->GetName() == L"FireLizard")
			{
				pos = other->GetOwner()->GetComp<Transform>()->GetPosition();
				object::Instantiate<Effect_Hit>(pos, eLayerType::Effect, SceneManager::GetActiveScene());
			}
			else
			{
				pos = other->GetOwner()->GetComp<Transform>()->GetPosition();
				object::Instantiate<Effect_Hit>(pos, eLayerType::Effect, SceneManager::GetActiveScene());
				mProj->SetState(GameObject::eState::Dead);
			}
		}
		else
		{
			Vector3 pos = other->GetOwner()->GetComp<Transform>()->GetPosition();
			object::Instantiate<Effect_Hit>(pos, eLayerType::Effect, SceneManager::GetActiveScene());
			mProj->SetState(GameObject::eState::Dead);
		}
	}
	void SCRIPT_MobProjectile::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_MobProjectile::OnCollisionExit(Collider2D* other)
	{
	}
	float SCRIPT_MobProjectile::GetSpeed()
	{
		if (mProjOwner != nullptr)
			return mProjOwner->GetStat().mSpeed;
		else
			return 50.0f;
	}
	float SCRIPT_MobProjectile::GetRange()
	{
		if (mProjOwner != nullptr)
			return mProjOwner->GetStat().mRange;
		else
			return 80.0f;
	}
}