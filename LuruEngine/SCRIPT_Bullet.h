#pragma once
#include "..\Engine_SOURCE\sgScript.h"
#include "Gobj_Player.h"
#include "Gobj_Bullet.h"


namespace sg
{
	class SCRIPT_Bullet : public Script
	{
	public:
		virtual void Initialize();
		virtual void Update();

		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other);
		virtual void OnCollisionExit(Collider2D* other);

		float GetDistance()
		{
			Vector3 currentPos = mBullet->GetComp<Transform>()->GetPosition();
			Vector2 distance = Vector2(currentPos.x - mLastPos.x, currentPos.y - mLastPos.y);
			return distance.Length();
		}

		Vector2 GetDirection()
		{
			Vector2 direction = Vector2(mLastPos.x - mFirstPos.x, mLastPos.y - mFirstPos.y);
			direction.Normalize();
			return direction;
		}
		float GetAngle(Vector2 dir)
		{
			float angleRad = std::acos(dir.x); // acos 함수를 사용하여 x축과의 각도를 구한다.
			if (dir.y < 0) // 방향 벡터의 y값이 음수면 각도를 음수로 변환한다.
			{
				angleRad = -angleRad;
			}
			return angleRad * 180.0f / 3.141592f;
		}
		float GetAngleInRadian(float degree)
		{
			return degree * (3.141592f / 180.0f);
		}
		Vector2 GetRoboBeamPos(float radius, float angle)
		{
			float x = radius * cos(angle) + mFirstPos.x;
			float y = radius * sin(angle) + mFirstPos.y;

			return Vector2(x, y);
		}



		void GetLastPos(int n);


	private:

		UINT mThisNum;
		UINT mTotalProjs;

		Gobj_Bullet* mBullet;
		eBulletType mBulletType;
		Gobj_Character* mBulletOwner;
		Gobj_Player* mPlayer;
		float mTime;
		float mTotalDuration;
		bool IsLaunched;

		Vector3 mFirstPos;
		Vector3 mLastPos;
		Vector3 mCurPos;

	};
}
