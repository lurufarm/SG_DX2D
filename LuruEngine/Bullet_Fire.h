#pragma once
#include "Gobj_MobProjectile.h"

namespace sg
{
	class Bullet_Fire : public Gobj_MobProjectile
	{
	public:
		Bullet_Fire(Gobj_Monster* BulletOwner);
		~Bullet_Fire();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		class ParticleSystem* mPs;
		float mTime;
	};
}
