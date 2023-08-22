#include "SCRIPT_Bullet.h"
#include "..\Engine_SOURCE\sgObject.h"
#include "Gobj_Character.h"
#include "Gobj_Player.h"
#include "Effect_Hit.h"
#include "Effect_Explosion.h"
#include "Effect_FirePlate.h"

extern sg::Gobj_Player* Player;

namespace sg
{
	void SCRIPT_Bullet::Initialize()
	{
		mTime = 0.0f;
		mBullet = (Gobj_Bullet*)GetOwner();
		mBulletType = mBullet->GetBulletType();
		mFirstPos = mBullet->GetFirstPos();
		mLastPos = mBullet->GetLastPos();
		IsLaunched = false;
		mTotalDuration = GetDistance() / 100.0f;

		mPlayer = Player;
		mBulletOwner = mBullet->GetBulletOwner();

		if (mBullet->GetBulletType() == eBulletType::Cheese)
		{
			Vector2 direction = GetDirection();
			float angleRad = std::acos(direction.x); // acos() 함수를 사용하여 x축과의 각도를 구합니다.
			if (direction.y < 0) // 방향 벡터의 y값이 음수면 각도를 음수로 변환합니다.
			{
				angleRad = -angleRad;
			}
			float angleDegree = (angleRad * 180.0f / 3.1415926535f) - 90.0f;
			
			Transform* tr = mBullet->GetComp<Transform>();
			tr->SetRotation(Vector3(0.0f, 0.0f, angleDegree));
		}


	}
	void SCRIPT_Bullet::Update()
	{
		mTime += Time::DeltaTime();
		float t = mTime / mTotalDuration;
		Vector3 curPos;
		if (mBulletType == eBulletType::Cheese)
		{
			curPos = mBullet->GetFirstPos() + t * (mLastPos - mFirstPos);
			curPos.z = -1.0f;
			mBullet->GetComp<Transform>()->SetPosition(curPos);
		}

		if (mBulletType == eBulletType::Lucy) // 포물선을 그리는 Projectile
		{
			float curveHeight = 20.0f; // 곡선의 높이
			float curveDuration = mTotalDuration * 0.7; // 곡선 운동 시간

			// 시간의 변화량을 계산
			//float deltaTime = Time::DeltaTime();
			float t = mTime / curveDuration;
			//mTime += deltaTime;

			// 포물선 곡선을 따르도록 x, y, z 좌표 계산
			float xDist = mLastPos.x - mFirstPos.x; // x 좌표의 이동 거리
			float yDist = mLastPos.y - mFirstPos.y; // y 좌표의 이동 거리
			float x = mFirstPos.x + t * xDist;
			float y = mFirstPos.y + t * yDist + curveHeight * 4.0f * t * (1.0f - t);
			float z = -1.0f;

			curPos = Vector3(x, y, z);
			mBullet->GetComp<Transform>()->SetPosition(curPos);

			// 운동이 끝나면 총알을 삭제하거나 비활성화 처리 등을 수행
			if (t >= 1.0f)
			{
				object::Instantiate<Effect_FirePlate>(curPos, eLayerType::Effect, SceneManager::GetActiveScene());
				object::Instantiate<Effect_Explosion>(curPos, eLayerType::Effect, SceneManager::GetActiveScene());
				mBullet->SetState(GameObject::eState::Dead);
			}
		}


		// Bullet State Changing : 사정거리 이상이 되면 사라진다
			Vector2 distance = Vector2(curPos.x - mBullet->GetFirstPos().x, curPos.y - mBullet->GetFirstPos().y);
			float dislength = distance.Length();
		if (dislength >= mPlayer->GetChar()->GetStat().mRange)
		{
			mBullet->SetState(GameObject::eState::Dead);
		}
	}
	void SCRIPT_Bullet::OnCollisionEnter(Collider2D* other)
	{
		Vector3 pos = other->GetOwner()->GetComp<Transform>()->GetPosition();
		object::Instantiate<Effect_Hit>(pos, eLayerType::Effect, SceneManager::GetActiveScene());

		if (mBullet->GetBulletType() == eBulletType::Lucy)
		{
			object::Instantiate<Effect_FirePlate>(Vector3(pos.x, pos.y, pos.z + 0.01f), eLayerType::Effect, SceneManager::GetActiveScene());
			object::Instantiate<Effect_Explosion>(pos, eLayerType::Effect, SceneManager::GetActiveScene());
		}
		GetOwner()->SetState(GameObject::eState::Dead);
	}
	void SCRIPT_Bullet::OnCollisionStay(Collider2D* other)
	{
	}
	void SCRIPT_Bullet::OnCollisionExit(Collider2D* other)
	{

	}
}