#pragma once
#include "Gobj_MobProjectile.h"

namespace sg
{
	class Bullet_SKGroundFire;
	class Bullet_SKGroundFires : public GameObject
	{
	public:
		Bullet_SKGroundFires(Gobj_Monster* BulletOwner);
		~Bullet_SKGroundFires();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void RandAngle();

	private:

		float mAngle;
		Bullet_SKGroundFire* mBullets[4];
		Gobj_Monster* mProjOwner;
	};
}
