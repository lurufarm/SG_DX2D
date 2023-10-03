#pragma once
#include "Gobj_MobProjectile.h"

namespace sg
{
	class Bullet_LightningOrb : public Gobj_MobProjectile
	{
	public:
		Bullet_LightningOrb(Gobj_Monster* BulletOwner);
		~Bullet_LightningOrb();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		class Animator* mAni;

	};
}
