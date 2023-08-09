#pragma once
#include "Gobj_MobProjectile.h"

namespace sg
{
	class Bullet_PoisonOrb : public Gobj_MobProjectile
	{
	public:
		Bullet_PoisonOrb(Gobj_Monster* BulletOwner);
		virtual ~Bullet_PoisonOrb();
		
		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		class Animator* mAni;

	};
}
