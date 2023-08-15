#pragma once
#include "Gobj_MobProjectile.h"

namespace sg
{
	class Bullet_SlicedApple : public Gobj_MobProjectile
	{
	public:
		Bullet_SlicedApple(Vector3 fPos, int dir);
		~Bullet_SlicedApple();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:
		class Animator* mAni;
	};
}
