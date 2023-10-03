#pragma once
#include "..\Engine_SOURCE\sgScript.h"
#include "Gobj_Player.h"
#include "Gobj_MobProjectile.h"


namespace sg
{
	class SCRIPT_MobProjectile : public Script
	{
	public:
		virtual void Initialize();
		virtual void Update();

		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other);
		virtual void OnCollisionExit(Collider2D* other);

		float GetDistance()
		{
			Vector3 currentPos = mProj->GetComp<Transform>()->GetPosition();
			Vector2 distance = Vector2(currentPos.x - mLastPos.x, currentPos.y - mLastPos.y);
			return distance.Length();
		}

		Vector2 GetDirection()
		{
			Vector2 direction = Vector2(mLastPos.x - mFirstPos.x, mLastPos.y - mFirstPos.y);
			direction.Normalize();
			return direction;
		}

		void LastPos_RandomDir()
		{
			const float PI = 3.141592;
			float angle = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * 2 * PI);

			// random distance
			float distance = 30.0f;
			float randomDistance = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * distance);

			// angle + distance
			mLastPos.x += randomDistance * cos(angle);
			mLastPos.y += randomDistance * sin(angle);

		}


		bool GetProjActivated() { return IsActivated; }
		Gobj_Monster* GetProjOwner() { return mProjOwner; }
		float GetSpeed();
		float GetRange();

	private:


		Gobj_MobProjectile* mProj;
		eMProjType mProjType;
		Gobj_Monster* mProjOwner;
		Gobj_Player* mTarget;
		float mTime;
		float mTotalDuration;
		bool IsLaunched;
		bool IsActivated;

		Vector3 mFirstPos;
		Vector3 mLastPos;

		const float PI = 3.141592;

	};
}
