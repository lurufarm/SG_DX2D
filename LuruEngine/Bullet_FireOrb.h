#pragma once
#include "Gobj_MobProjectile.h"

namespace sg
{
	class Bullet_FireOrb : public Gobj_MobProjectile
	{
	public:
		Bullet_FireOrb(Gobj_Monster* BulletOwner);
		Bullet_FireOrb(Vector2 dir, Gobj_Monster* BulletOwner);
		~Bullet_FireOrb();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		class Animator* mAni;


	};
}
