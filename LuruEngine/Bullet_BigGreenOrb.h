#pragma once
#include "Gobj_MobProjectile.h"

namespace sg
{
	class Bullet_GreenOrb;
	class Bullet_BigGreenOrb : public Gobj_MobProjectile
	{
	public:
		Bullet_BigGreenOrb(Gobj_Monster* BulletOwner);
		~Bullet_BigGreenOrb();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void RandAngle();

	private:
		class Animator* mAni;
		float mAngle;
		Bullet_GreenOrb* mBullets[12];
	};
}
