#pragma once
#include "Gobj_Effect.h"
#include "Gobj_Bullet.h"
#include "Gobj_MobProjectile.h"

namespace sg
{
	class Bullet_SKGroundFire : public Gobj_MobProjectile
	{
	public:
		Bullet_SKGroundFire(Vector2 dir, Gobj_Monster* BulletOwner);
		~Bullet_SKGroundFire();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		Vector2 mDir;
	private:
		class Animator* mAni;
	};
}
