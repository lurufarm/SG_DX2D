#pragma once
class Bullet_Spear
{
};

#pragma once
#include "Gobj_MobProjectile.h"

namespace sg
{
	class Bullet_Spear : public Gobj_MobProjectile
	{
	public:
		Bullet_Spear(Gobj_Monster* BulletOwner);
		~Bullet_Spear();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		float mTime;
	};
}
