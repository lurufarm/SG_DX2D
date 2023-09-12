#include "SCRIPT_Bullet.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Gobj_Character.h"
#include "Gobj_Player.h"
#include "Effect_Hit.h"
#include "Effect_Explosion.h"
#include "Effect_FirePlate.h"
#include "Effect_LaserHit.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	void SCRIPT_Bullet::Initialize()
	{

		mTime = 0.0f;
		mBullet = (Gobj_Bullet*)GetOwner();
		mBulletType = mBullet->GetBulletType();
		IsLaunched = false;
		mPlayer = Player;
		mBulletOwner = mBullet->GetBulletOwner();

		mTotalProjs = mBulletOwner->GetStat().mProjectileCount;
		mThisNum = mBullet->GetThisNum();
		mFirstPos = mBullet->GetFirstPos();
		mCurPos = mFirstPos;
		GetLastPos(mThisNum);
		mTotalDuration = GetDistance() / 100.0f;

		if (mBulletType == eBulletType::Cheese)
		{
			Vector2 direction = GetDirection();
			float angleDegree = GetAngle(direction) - 90.0f;
			Transform* tr = mBullet->GetComp<Transform>();
			tr->SetRotation(Vector3(0.0f, 0.0f, angleDegree));
		}
		else if (mBulletType == eBulletType::Robo)
		{
			mLastPos = mPlayer->GetTarget()->GetComp<Transform>()->GetPosition();
			Vector2 direction = GetDirection();
			float angleDegree = GetAngle(direction) - 90.0f;
			float angleRadian = GetAngleInRadian(angleDegree + 90.0f);
			Vector2 pos = GetRoboBeamPos(160.0f, angleRadian);
			Vector3 lastpos = Vector3(pos.x, pos.y, -1.0f);
			Transform* tr = mBullet->GetComp<Transform>();
			tr->SetRotation(Vector3(0.0f, 0.0f, angleDegree));
			tr->SetPosition(lastpos);
		}
	}
	void SCRIPT_Bullet::Update()
	{
		mTime += Time::DeltaTime();
		if (mBulletType == eBulletType::Cheese)
		{
			Vector3 Direction = mLastPos - mFirstPos;
			Direction.Normalize();
			mCurPos += mPlayer->GetStat().mAttackSpeed * Time::DeltaTime() * Direction;
			mCurPos.z = -1.0f;
			mBullet->GetComp<Transform>()->SetPosition(mCurPos);

			Vector2 distance = Vector2(mCurPos.x - mBullet->GetFirstPos().x, mCurPos.y - mBullet->GetFirstPos().y);
			float dislength = distance.Length();
			if (dislength >= mPlayer->GetChar()->GetStat().mRange * 1.5f)
			{
				mBullet->SetState(GameObject::eState::Dead);
			}
		}

		if (mBulletType == eBulletType::Lucy) // 포물선을 그리는 Projectile
		{
			float curveHeight = 20.0f; // 곡선의 높이
			//float curveDuration = mTotalDuration * 0.7; // 곡선 운동 시간
			float curveDuration = mTotalDuration * (mBulletOwner->GetStat().mAttackSpeed / 100.0f); // 곡선 운동 시간

			// 시간의 변화량을 계산
			float t = mTime / curveDuration;

			// 포물선 곡선을 따르도록 x, y, z 좌표 계산
			float xDist = mLastPos.x - mFirstPos.x; // x 좌표의 이동 거리
			float yDist = mLastPos.y - mFirstPos.y; // y 좌표의 이동 거리
			float x = mFirstPos.x + t * xDist;
			float y = mFirstPos.y + t * yDist + curveHeight * 4.0f * t * (1.0f - t);
			float z = -1.0f;

			mCurPos = Vector3(x, y, z);
			mBullet->GetComp<Transform>()->SetPosition(mCurPos);

			// 아무도 맞지 않아도 도착하면 터짐
			if (t >= 1.0f)
			{
				object::Instantiate<Effect_FirePlate>(mCurPos, eLayerType::Effect, SceneManager::GetActiveScene());
				object::Instantiate<Effect_Explosion>(mCurPos, eLayerType::Effect, SceneManager::GetActiveScene());
				mBullet->SetState(GameObject::eState::Dead);
			}
		}


		 //모든 Bullet은 사정거리 이상이 되면 사라진다.

	}
	void SCRIPT_Bullet::OnCollisionEnter(Collider2D* other)
	{
		Vector3 pos = other->GetOwner()->GetComp<Transform>()->GetPosition();

		if (mBullet->GetBulletType() == eBulletType::Lucy)
		{
			object::Instantiate<Effect_FirePlate>(Vector3(pos.x, pos.y, pos.z + 0.01f), eLayerType::Effect, SceneManager::GetActiveScene());
			object::Instantiate<Effect_Explosion>(pos, eLayerType::Effect, SceneManager::GetActiveScene());
		}
		else if (mBulletType == eBulletType::Robo)
			object::Instantiate<Effect_LaserHit>(Vector3(pos.x, pos.y, pos.z - 1.0f), eLayerType::Player_Effect, SceneManager::GetActiveScene());

		if (mBulletType != eBulletType::Robo)
		{
			object::Instantiate<Effect_Hit>(pos, eLayerType::Effect, SceneManager::GetActiveScene());
			GetOwner()->SetState(GameObject::eState::Dead);
		}
	}
	void SCRIPT_Bullet::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_Bullet::OnCollisionExit(Collider2D* other)
	{

	}
	void SCRIPT_Bullet::GetLastPos(int n)
	{
		mLastPos = mBullet->GetLastPos();

		if (n >= 2)
		{
			if (n % 2 == 0)
			{
				float angledegree = 10.0f * n;
				float angle = angledegree * (3.141592 / 180.0f);
				Vector2 direction = GetDirection();
				mLastPos.x = cos(angle) * direction.x - sin(angle) * direction.y;
				mLastPos.y = sin(angle) * direction.x + cos(angle) * direction.y;
				mLastPos += mFirstPos;
			}
			else
			{
				float angledegree = -10.0f * (n - 1.0f);
				float angle = angledegree * (3.141592 / 180.0f);
				Vector2 direction = GetDirection();
				mLastPos.x = cos(angle) * direction.x - sin(angle) * direction.y;
				mLastPos.y = sin(angle) * direction.x + cos(angle) * direction.y;
				mLastPos += mFirstPos;
			}
		}
	}
}