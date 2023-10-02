#pragma once
#include "Gobj_MobProjectile.h"

namespace sg
{
	class Bullet_BloodSpit : public Gobj_MobProjectile
	{
	public:
		Bullet_BloodSpit(Gobj_Monster* BulletOwner, Vector3 dir);
		~Bullet_BloodSpit();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

	};
}
