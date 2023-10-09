#pragma once
#include "Gobj_MobProjectile.h"

namespace sg
{
	class Bullet_WhirlWind : public Gobj_MobProjectile
	{
	public:
		Bullet_WhirlWind(Gobj_Monster* BulletOwner);
		~Bullet_WhirlWind();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		float mTime;
	};
}
