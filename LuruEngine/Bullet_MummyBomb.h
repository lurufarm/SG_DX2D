#pragma once
#include "Gobj_MobProjectile.h"

namespace sg
{
	class Bullet_MummyBomb : public Gobj_MobProjectile
	{
	public:
		Bullet_MummyBomb(Gobj_Monster* BulletOwner);
		~Bullet_MummyBomb();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		class Animator* mAni;

	};
}
