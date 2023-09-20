#pragma once
#include "..\Engine_SOURCE\sgGameObject.h"
#include "Gobj_MobProjectile.h"

namespace sg
{
	class Bullet_FireOrb;
	class Bullet_FireOrbs : public GameObject
	{
	public:
		Bullet_FireOrbs(Gobj_Monster* BulletOwner);
		~Bullet_FireOrbs();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void RandAngle();

	private:

		float mAngle;
		Bullet_FireOrb* mBullets[15];
		Gobj_Monster* mProjOwner;

	};
}
