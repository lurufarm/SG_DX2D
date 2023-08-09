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

	private:


		Gobj_Bullet* mBullet;
		eBulletType mBulletType;
		GameObject* mBulletOwner;
		Gobj_Player* mPlayer;
		float mTime;
		float mTotalDuration;
		bool IsLaunched;

		Vector3 mFirstPos;
		Vector3 mLastPos;


	};
}
