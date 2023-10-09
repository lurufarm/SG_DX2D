#pragma once
#include "Gobj_MobProjectile.h"

namespace sg
{
	class Bullet_GreenOrb : public Gobj_MobProjectile
	{
	public:
		Bullet_GreenOrb(Gobj_Monster* BulletOwner);
		Bullet_GreenOrb(Vector2 dir, class Bullet_BigGreenOrb* BOrb);
		~Bullet_GreenOrb();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		class Animator* mAni;
		class Bullet_BigGreenOrb* mBOrb;


	};
}
