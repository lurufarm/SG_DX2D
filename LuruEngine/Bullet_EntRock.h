#pragma once
#include "Gobj_MobProjectile.h"

namespace sg
{
	class Bullet_EntRock : public Gobj_MobProjectile
	{
	public:
		Bullet_EntRock(Gobj_Monster* BulletOwner);
		~Bullet_EntRock();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		class Animator* mAni;

	};
}
