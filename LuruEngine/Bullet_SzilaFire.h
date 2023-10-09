#pragma once
#include "Gobj_Bullet.h"

namespace sg
{
	class Bullet_SzilaFire : public Gobj_Bullet
	{
	public:
		Bullet_SzilaFire();
		Bullet_SzilaFire(int num);
		~Bullet_SzilaFire();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

	private:

		class ParticleSystem* mPs;

	};
}
