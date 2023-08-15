#pragma once
#include "Gobj_MobProjectile.h"

namespace sg
{
	class Bullet_Apple : public Gobj_MobProjectile
	{
	public:
		Bullet_Apple(Gobj_Monster* BulletOwner);
		~Bullet_Apple();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		class Animator* mAni;
	};
}
